# Usage

## Connecting to Jenkins

### Accessing Jenkins
- Open a web browser and navigate to `http://jenkins.example.com`.
- Enter the username and password as configured during the Jenkins setup.

### Navigating the Jenkins Dashboard
- The main dashboard displays all the Jenkins jobs and their current status.
- You can view build histories, manage plugins, and configure system settings from the dashboard.

## Jenkins Folders

### 1. Whanos Base Images
- **Description**: Contains the base Docker images for "Whanos".
- **Purpose**: Organizes jobs related to building Docker base images for different programming languages.

### 2. Projects
- **Description**: Houses the available projects in "Whanos".
- **Purpose**: Serves to organize jobs specific to individual "Whanos" projects.

## Jenkins Jobs

### Building Base Images for Each Language
- **Jobs Created**: For each language in `["c", "java", "javascript", "python", "befunge"]`, a Freestyle job is created under the "Whanos base images" folder.
- **Job Name**: "whanos-\<language\>" (e.g., "whanos-java").
- **Steps**: Each job executes a shell script to build a Docker image using a language-specific Dockerfile.
- **Utility**: Automates the creation of Docker base images for various development environments.

### Build All Base Images
- **Description**: Builds all the base images.
- **Type**: Freestyle Job.
- **Steps**: Uses `publishers -> downstream` mechanism to trigger building all base images once this job is executed.
- **Utility**: Enables building all base images in a single operation, ensuring consistency among them.

### Link-Project
- **Description**: Dynamically creates a new job for a specific project within the "Projects" folder.
- **Type**: Freestyle Job with parameters.
- **Parameters**:
  - `DISPLAY_NAME`: Display name for the job.
  - `GIT_URL`: Git repository URL.
  - `GIT_BRANCH`: Git branch to use.
  - `REGISTRY_URL`: Registry URL to store the Docker image.
- **Steps**:
  - Adds `github.com` to known hosts for SSH.
  - Uses DSL to dynamically create a new Freestyle job for the specified project, with SCM triggers, pre-build cleanup, and a shell script for deployment.
- **Utility**: Allows adding new projects to Jenkins dynamically, automating their setup and deployment.

## Special Configuration for Private Repositories

### SSH Key Configuration for `link-project` Job

The `link-project` job in Jenkins is designed to dynamically create new jobs for specific projects. For accessing private Git repositories, it's essential to set up SSH keys correctly.

#### SSH Key in Job Description
- **Job**: `link-project`
- **Key Location**: The SSH public key required for repository access is provided in the job's description (`Clé SSH publique:\n\n{{public_key}}`).
- **Purpose**: This key must be added to the respective Git repository (or Git account settings) to enable Jenkins to clone and interact with private repositories.

#### Adding the SSH Key
1. **Locate the Key**: Find the SSH public key in the description of the `link-project` job in Jenkins.
2. **Add to Git Repository**:
   - For GitHub: Go to [github.com/settings/ssh/new](https://github.com/settings/ssh/new) and paste ssh key
   - For other Git services: Follow a similar process to add the deploy key to your repository or account.
3. **Verify Connectivity**: Once the key is added, Jenkins should be able to interact with the private repository, allowing the `link-project` job to clone and execute tasks on the repository.

---

[README](../README.md) -  [Required Resources](/doc/required_ressources.md) - [Configs files](/doc/config_files.md) - [Start Install](/doc/start_install.md) - [Usage](/doc/usage.md)  - [Docker Image](/doc/docker_image.md)