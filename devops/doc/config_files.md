# Configs files

## Inventory File ([inventory.yml](../inventory.yml))
- **Purpose**: The inventory file in Ansible is used to define and group the servers or nodes that our playbooks will target.

### Structure of [inventory.yml](../inventory.yml)
The [inventory.yml](../inventory.yml) file is structured in a YAML format, allowing easy readability and management. Below is an example structure:

```yaml
all:
  children:
    redis:
      vps:
        main:
          ansible_user:
          ansible_host:
```

## Group Variables Files
Ansible's group variables files allow us to define variables that are specific to certain groups of hosts, making our playbooks more flexible and maintainable.

### Jenkins Group Variables ([group_vars/jenkins.yml](../group_vars/jenkins.yml))
- **Purpose**: Holds configuration settings specific to Jenkins.
- **Example Structure**:
```yaml
username:
password:
```

### NGINX Group Variables ([group_vars/nginx.yml](../group_vars/nginx.yml))
- **Purpose**: Contains variables specific to Nginx configurations, particularly related to domain settings and SSL.
- **Example Structure**:
```yaml
registry_domain:
jenkins_domain:
mail_certbot:
```

## Best Practices
- **Security**: For [group_vars/jenkins.yml](../group_vars/jenkins.yml), especially with sensitive data like password, consider using Ansible Vault to encrypt these values.
```sh
ansible-vault encrypt ./group_vars/jenkins.yml
```
- **Consistency**: Ensure that the domain names in [group_vars/nginx.yml](../group_vars/nginx.yml) match those configured in your DNS and are consistent with the inventory setup.

---

[README](../README.md) -  [Required Resources](/doc/required_ressources.md) - [Configs files](/doc/config_files.md) - [Start Install](/doc/start_install.md) - [Usage](/doc/usage.md)  - [Docker Image](/doc/docker_image.md)