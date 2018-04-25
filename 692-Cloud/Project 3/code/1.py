#http://192.168.122.237

from libcloud.compute.types import Provider
from libcloud.compute.providers import get_driver

auth_username = 'demo'
auth_password = '37and34'
# auth_url = 'http://192.168.122.237:9696'
# auth_url = 'http://192.168.122.237:35357'
# auth_url = 'http://192.168.122.237:5000'
# auth_url = 'http://192.168.122.237:11211'
# auth_url = 'http://192.168.122.237:11211/identity'
# auth_url = 'http://192.168.122.237'
# auth_url = 'http://192.168.122.237/identity'
# auth_url = 'http://192.168.122.237/v2.0/tokens'
auth_url = 'http://192.168.122.237/identity/v3/auth/tokens'
project_name = 'demo'
region_name = 'RegionOne'
# region_name = ''

provider = get_driver(Provider.OPENSTACK)
conn = provider(auth_username,
				auth_password,
				ex_force_auth_url=auth_url,
				ex_force_auth_version='3.x_password',
				ex_tenant_name=project_name,
				ex_force_service_region=region_name)

# listing available boot images
images = conn.list_images()
for image in images:
	print(image)

print("")
# Listint VM predefined sizes
flavors = conn.list_sizes()
for flavor in flavors:
	print(flavor)

print()
# Preselecting VM boot image
#image_id = "cfe940bd-15c5-44fd-8aa2-c5f2e5373db2" #cirros
image_id = "4c6a8bbf-3b19-403c-9b91-a0186ecc1456" #ubuntu
image = conn.get_image(image_id)
print(image)

print()
# Preselecting VM sizes
flavor_id = 'd2'
flavor = conn.ex_get_size(flavor_id)
print(flavor)

print()
# Making a new VM
# instance_name = 'ubuntu_test_instance'
# testing_instance = conn.create_node(name=instance_name, image=image, size=flavor)
# print(testing_instance)

print()
#listing available VMs
instances = conn.list_nodes()
for instance in instances:
	print(instance)

print()

#conn.destroy_node(testing_instance)

print()

# make sure there is an SSH key
print('Checking for existing SSH key pair...')
keypair_name = 'Genserver'
pub_key_file = '~/.ssh/id_rsa.pub'
keypair_exists = False
for keypair in conn.list_key_pairs():
	if keypair.name == keypair_name:
		keypair_exists = True

if keypair_exists:
	print('Keypair ' + keypair_name + ' already exists. Skipping import.')
else:
	print('adding keypair...')
	conn.import_key_pair_from_file(keypair_name, pub_key_file)

for keypair in conn.list_key_pairs():
	if(keypair.name == "demokey"): conn.delete_key_pair(keypair)
	print(keypair)

print()

# making a security group
print('Checking for existing security group...')
security_group_name = 'all-in-one'
security_group_exists = False
for security_group in conn.ex_list_security_groups():
	if security_group.name == security_group_name:
		all_in_one_security_group = security_group
		security_group_exists = True

if security_group_exists:
	print('Security Group ' + all_in_one_security_group.name + ' already exists. Skipping creation.')
else:
	all_in_one_security_group = conn.ex_create_security_group(security_group_name, 'network access for all-in-one application.')
	conn.ex_create_security_group_rule(all_in_one_security_group, 'TCP', 80, 80)
	conn.ex_create_security_group_rule(all_in_one_security_group, 'TCP', 22, 22)

for security_group in conn.ex_list_security_groups():
	print(security_group)

userdata = '''#!/usr/bin/env bash
curl -L -s https://git.openstack.org/cgit/openstack/faafo/plain/contrib/install.sh | bash -s -- \
	-i faafo -i messaging -r api -r worker -r demo
'''

print()

#make a VM with the params configured above
print('Checking for existing instance...')
instance_name = 'ubuntu-test'
instance_exists = False
for instance in conn.list_nodes():
	if instance.name == instance_name:
		testing_instance = instance
		instance_exists = True

if instance_exists:
	print('Instance ' + testing_instance.name + ' already exists. Skipping creation.')
else:
	testing_instance = conn.create_node(name=instance_name,
										image=image,
										size=flavor,
										ex_keyname=keypair_name,
										ex_userdata=userdata,
										ex_security_groups=[all_in_one_security_group])
	conn.wait_until_running([testing_instance])

for instance in conn.list_nodes():
	print(instance)

# Do some networking work

private_ip = None
if len(testing_instance.private_ips):
    private_ip = testing_instance.private_ips[0]
    print('Private IP found: {}'.format(private_ip))

public_ip = None
if len(testing_instance.public_ips):
    public_ip = testing_instance.public_ips[0]
    print('Public IP found: {}'.format(public_ip))

print('Checking for unused Floating IPs...')
unused_floating_ip = None
for floating_ip in conn.ex_list_floating_ips():
    if not floating_ip.node_id:
        unused_floating_ip = floating_ip
        break

if not unused_floating_ip and len(conn.ex_list_floating_ip_pools()):
    pool = conn.ex_list_floating_ip_pools()[0]
    print('Allocating new Floating IP from pool: {}'.format(pool))
    unused_floating_ip = pool.create_floating_ip()

if public_ip:
    print('Instance ' + testing_instance.name + ' already has a public ip. Skipping attachment.')
elif unused_floating_ip:
    conn.ex_attach_floating_ip_to_node(testing_instance, unused_floating_ip)

actual_ip_address = None
if public_ip:
    actual_ip_address = public_ip
elif unused_floating_ip:
    actual_ip_address = unused_floating_ip.ip_address
elif private_ip:
    actual_ip_address = private_ip

print('The Fractals app will be deployed to http://{}'.format(actual_ip_address))