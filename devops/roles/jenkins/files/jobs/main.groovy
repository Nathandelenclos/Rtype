folder("Projects") {
	description("The available projects")
}

freeStyleJob("link-project") {
	description('SSH public key:\n\n{{public_key}}')
	parameters {
		stringParam("PROJECT_NAME", null, "Name of project")
		stringParam("DISPLAY_NAME", null, "Display name for the job")
		stringParam("GIT_URL", null, 'Git repository url')
		stringParam("GIT_BRANCH", "master", "Git branch to use")
		stringParam("REGISTRY_URL", "{{registry_domain}}", "Registry to store docker image")
		stringParam("WEBHOOK_TEAMS", null, "Webhook url for teams")
	}
	steps {
		shell("ssh-keyscan github.com >> /var/lib/jenkins/.ssh/known_hosts")
		dsl {
			text('''
				freeStyleJob("Projects/$DISPLAY_NAME") {
				    description("Project $PROJECT_NAME")
				    properties {
                        office365ConnectorWebhooks {
                            webhooks {
                                webhook {
                                    name("$DISPLAY_NAME")
                                    url("$WEBHOOK_TEAMS")
                                    startNotification(false)
                                    notifySuccess(true)
                                    notifyAborted(false)
                                    notifyNotBuilt(false)
                                    notifyUnstable(true)
                                    notifyFailure(true)
                                    notifyBackToNormal(true)
                                    notifyRepeatedFailure(false)
                                    timeout(30000)
                                }
                            }
                        }
                    }
					scm {
						git {
							remote {
								name("origin")
								branch("$GIT_BRANCH")
								url("$GIT_URL")
							}
						}
					}
					triggers {
						scm("* * * * *")
					}
					wrappers {
						preBuildCleanup()
					}
					steps {
						shell("/var/lib/jenkins/deploy.sh \\"$PROJECT_NAME\\" \\"$REGISTRY_URL\\"")
					}
				}
			''')
		}
	}
}
