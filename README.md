# cypress

[[_TOC_]]

[Cypress](https://docs.cypress.io/app/get-started/why-cypress) is a tool that allows you to test webpages. Use it to write and run Cypress test scripts (called "specs") which automate procedures like clicking buttons, typing text, and verifying that the webpages respond correctly. You can write them in Cypress GUI or in any other editor. This project contains all the files needed to build Docker image `cypress`, which contains dependencies, Cypress, and web browsers. You can use the image in a pipeline, or you can make a container locally and work in it. You will have to write your own Cypress files: specs, config files, support files, cypress.env.json. The image does not provide any of these.

Some projects use the image in their pipelines. They use floating image `registry.devops.iskratel.cloud/devops/containers/cypress:stable`. The image is built in DevOps/containers/cypress pipeline. When a developer wants to make a new release – as in to build a production image and make that image immediately available to our pipelines – he/she tags DevOps/containers/cypress in GitLab. Its pipeline builds an image from the commit. Then, it pushes the image to the registry twice, once with the GitLab tag as its tag, and then again with floating tag `stable`. Thus, we do not have to update the image in other projects' pipelines each time we make a new one. Tagging the image twice also allows us to keep track of which image is currently used in our pipelines, since we know that `stable` is always an alias for the latest tag. If we discover an error in `stable`, we can rebuild a previous tag, and make it be the `stable` until the error is fixed. The other images have the tag `[BRANCH]-[TIMESTAMP]-[HASH]`.

## Base image

Dockerfile uses an official Cypress image as the base image. Cypress provides several variants of official images: one contains dependencies, but no Cypress; another contains dependencies and browsers, but no Cypress ... Dockerfile uses the variant `cypress/included`, where everything possible is installed. [More in the official docs.](https://docs.cypress.io/app/continuous-integration/overview#Cypress-Docker-variants)

## Use in CI

Use the image in your pipelines. Project [DevOps/cicd-common](https://vmgitent.iskratel.si/devops/cicd-common) provides reusable CI jobs. Consult its documentation for recommended usage patterns. Your pipelines can also define custom CI jobs that use the image.

## Use locally

Pull the image from Nexus, replacing the tag if necessary:

```bash
docker pull registry.devops.iskratel.cloud/devops/containers/cypress:stable
docker tag registry.devops.iskratel.cloud/devops/containers/cypress:stable cypress:local
```

Or build the image locally:

```bash
docker build -t "cypress:local" --network "host" .
```

Make a container. If you plan to open Cypress GUI or any other GUI, make sure that X11 is installed and configured on host. Then run:

```bash
./scripts/docker_cnt_gui.sh
```

Explanation: The helper script uses the image to make and enter a background container with X11 files and variables. Read its docstring and comments for the details.

If you don't plan to open Cypress GUI or any other GUI, then you don't need X11. Cypress must have still permissions to read and write files on host (e.g. Cypress videos). The image already has users `root` (UID 0) and `node` (UID 1000). Get the host UID with `id -u`. If the host UID matches one of the users, run:

```bash
docker run -d --name cypress --net host -w "${PWD}" -v "${PWD}:${PWD}" -u "$(id -u)" cypress:local sleep inf
docker exec -it cypress bash
```

If the host UID doesn't match any, run:

```bash
docker run -d --name cypress --net host -w "${PWD}" -v "${PWD}:${PWD}" cypress:local sleep inf && \
user="$(id -nu)" && uid="$(id -u)" && gid="$(id -g)" && home="${HOME}" && \
docker exec -t cypress bash -c "groupadd -f -g ${gid} ${user} && useradd ${user} -u ${uid} -g ${gid} -d ${home} && chown ${uid}:${gid} -R ${home}" && \
docker exec -it -u "${user}" cypress bash
```

Explanation: The code makes and enters a background container that contains a new user with the host UID.

Once you are in the container, use the tools. Examples:

```bash
# Get help for Cypress.
cypress --help
# Open Cypress GUI in the foreground.
cypress open -P "${PWD}"
# Open Cypress GUI in the background.
cypress open -P "${PWD}" &
# Run a Cypress spec with browser GUI.
cypress run -P "${PWD}" -C cypress.config.js -b chrome -s deploy-core.e2e.spec.js --headed
# Run a Cypress spec without browser GUI.
cypress run -P "${PWD}" -C cypress.config.js -b chrome -s deploy-core.e2e.spec.js
# Use browser GUI by yourself.
google-chrome --no-sandbox &
```

The commands open GUIs like they would in a normal graphical environment:

![screenshot](./imgs/img1.PNG)

![screenshot](./imgs/img2.PNG)

The commands might log non-breaking messages, but still work as intended:

```text
Still waiting to connect to Chrome, retrying in 1 second (attempt 18/62)
Still waiting to connect to Chrome, retrying in 1 second (attempt 19/62)
Still waiting to connect to Chrome, retrying in 1 second (attempt 20/62)
```

```text
DevTools listening on ws://127.0.0.1:40909/devtools/browser/ecbe8a7e-3092-4bf6-b02f-b4ee7ae59232
libva error: vaGetDriverNameByIndex() failed with unknown libva error, driver_name = (null)
[998:0418/103642.837815:ERROR:gpu_memory_buffer_support_x11.cc(44)] dri3 extension not supported.
```

```text
[48:70:0306/160814.252630:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/dbus/system_bus_socket: No such file or directory
[48:75:0306/160818.452829:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/dbus/system_bus_socket: No such file or directory
[48:75:0306/160818.453268:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/dbus/system_bus_socket: No such file or directory
[48:70:0306/160818.468484:ERROR:bus.cc(399)] Failed to connect to the bus: Address does not contain a colon
[48:70:0306/160818.468541:ERROR:bus.cc(399)] Failed to connect to the bus: Address does not contain a colon
[48:70:0306/160818.487787:ERROR:bus.cc(399)] Failed to connect to the bus: Address does not contain a colon
[48:70:0306/160818.488328:ERROR:bus.cc(399)] Failed to connect to the bus: Address does not contain a colon
[48:112:0306/160818.622208:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/dbus/system_bus_socket: No such file or directory
[48:112:0306/160818.622367:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/dbus/system_bus_socket: No such file or directory
[48:112:0306/160818.624634:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/dbus/system_bus_socket: No such file or directory
[48:112:0306/160818.624831:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/dbus/system_bus_socket: No such file or directory
[48:112:0306/160818.624974:ERROR:bus.cc(399)] Failed to connect to the bus: Failed to connect to socket /run/dbus/system_bus_socket: No such file or directory
libva error: vaGetDriverNameByIndex() failed with unknown libva error, driver_name = (null)
[84:84:0306/160824.733936:ERROR:viz_main_impl.cc(186)] Exiting GPU process due to errors during initialization
```
