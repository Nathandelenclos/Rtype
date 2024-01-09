folder("Projects") {
	description("The available projets")
}

freeStyleJob("link-project") {
	description('Clé SSH publique:\n\n{{public_key}}')
	parameters {
		stringParam("PROJECT_NAME", null, "Name of project")
		stringParam("DISPLAY_NAME", null, "Display name for the job")
		stringParam("GIT_URL", null, 'Git repository url')
		stringParam("GIT_BRANCH", "master", "Git branch to use")
		stringParam("REGISTRY_URL", "{{registry_domain}}", "Registry to store docker image")
	}
	steps {
		shell("ssh-keyscan github.com >> /var/lib/jenkins/.ssh/known_hosts")
		dsl {
			text('''
				freeStyleJob("Projects/$DISPLAY_NAME") {
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
