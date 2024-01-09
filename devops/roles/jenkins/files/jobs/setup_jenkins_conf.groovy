import jenkins.model.*
def instance = Jenkins.getInstance()
def desc = instance.getDescriptorByType(jenkins.model.JenkinsLocationConfiguration.class)
desc.setUrl("{{jenkins_domain}}")
desc.save()