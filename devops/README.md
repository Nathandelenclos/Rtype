# [B-DOP-500] Whanos


The "B-DOP-500 Whanos" project focuses on automating application deployment in a Kubernetes cluster via Git. It supports multiple languages and involves configuring Jenkins for automation, creating Whanos images, and Kubernetes setup. The project integrates Docker, Jenkins, Ansible, and Kubernetes for efficient DevOps processes.

## About

The project "Whanos" involves several steps to set up a DevOps infrastructure:

1. **Repository Setup**: Create a Whanos-compatible repository containing the application code in a supported language (C, Java, JavaScript, Python, Befunge). The repository must follow specific structural requirements.

2. **Image Specifications**: Define Docker image specifications for each supported language. This includes standalone and base images, which are built based on certain criteria like default compiler version, detection criteria, and execution commands.

3. **Jenkins Configuration**: Set up a Jenkins instance for automation, including specific jobs for building base images, linking projects, and deploying applications.

4. **Kubernetes Integration**: Utilize Kubernetes for orchestrating the deployment of applications. This includes setting up a cluster and managing application deployment through `whanos.yml` files in each repository.

5. **Deployment and Evaluation**: Deploy the infrastructure online, likely using Ansible. The project will be evaluated on functionality, adherence to best practices, and documentation.

This summary provides a high-level overview of the key stages in the Whanos project. For detailed instructions and specifications, you should refer to the original document.

## Documentation

 - [Required Resources](/doc/required_ressources.md)
 - [Configs files](/doc/config_files.md)
 - [Start Install](/doc/start_install.md)
 - [Usage](/doc/usage.md)
 - [Docker Image](/doc/docker_image.md)

## Demo

[![Video](https://i.redd.it/o2uk0p3o0dy21.jpg)](https://youtu.be/rKKLFuDFF64)

## Contact

 - [Epitech](https://www.epitech.eu/) - Product Owner.
 - [Nathan Delenclos](https://github.com/Nathandelenclos) - Developer
 - [David Plouvier](https://github.com/DavidPlouvier) - Developer
 - [Simon Riembault](https://github.com/SimonRmblt) - Developer

## Subject

 [B-DOP-500_whanos.pdf](/B-DOP-500_whanos.pdf)