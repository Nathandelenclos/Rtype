# Docker Image Availability Post Project Linking

## Understanding the Workflow of `link-project` Job

### Overview
The `link-project` job in Jenkins not only sets up projects for continuous integration but also plays a crucial role in the continuous deployment process, particularly in the context of Docker images.

### Post-Linking Actions
- **Job**: `link-project`
- **Functionality**: Upon successfully linking a project, this job triggers a series of actions, including the building and pushing of the project's Docker image to a specified Docker registry.

### Docker Image Availability
- **Registry URL**: Specified in the `link-project` job parameters (e.g., `REGISTRY_URL: "{{registry_domain}}"`).
- **Image Accessibility**: Once the `link-project` job completes its execution, the Docker image of the linked project is built and pushed to the specified Docker registry.
- **Use Case**: This allows the Docker image to be readily available for deployment, testing, or further development stages.

## Accessing the Docker Image
1. **Locate the Image**: The Docker image can be found in the Docker registry specified in the `REGISTRY_URL` parameter.
2. **Pulling the Image**: Users can pull the Docker image from the registry using Docker commands, for example, `docker pull registry.example.com/project-image`.
3. **Deployment and Usage**: The pulled image can be used for deployment in various environments, further ensuring the consistency and reliability of the application.

---

[README](../README.md) -  [Required Resources](/doc/required_ressources.md) - [Configs files](/doc/config_files.md) - [Start Install](/doc/start_install.md) - [Usage](/doc/usage.md)  - [Docker Image](/doc/docker_image.md)