# 5g-cypress-test-vv

[[_TOC_]]


HOW TO PREPARE CYPRESS FOR USE ON YOUR LOCAL VM


## Get docker image

Pull the image from Nexus, replacing the tag if necessary:

```bash
docker pull registry.devops.iskratel.cloud/devops/containers/cypress:stable
docker tag registry.devops.iskratel.cloud/devops/containers/cypress:stable cypress:local
```

## Get GitLab projects

Get the following projects from GitLab:

[cypress](https://vmgitent.iskratel.si/devops/Containers/cypress)
Project includes a short manual on using cypress and some useful scripts
[i5g_fe](https://vmgitent.iskratel.si/MC5000AX/i5g-fe)
Project is the frontend of 5G system, it also includes current cypress tests
[MC5000AX_TOP](https://vmgitent.iskratel.si/MC5000AX/MC5000AX_TOP)
Project includes cypress config and env files with the latest relase data

```bash
git clone https://vmgitent.iskratel.si/devops/Containers/cypress.git
git clone https://vmgitent.iskratel.si/MC5000AX/i5g-fe.git
git clone https://vmgitent.iskratel.si/MC5000AX/MC5000AX_TOP.git
```

##	Update ENV with the latest NF tags

To update `cypress.env.json` located in `MC5000AX_TOP` with the latest NF tags, run:

```bash
wget https://nexus.devops.iskratel.cloud/repository/documentation/GP1010AX/3.0.0.0.220/release.json -O release_GP1010AX.json
./inject_cypress_env.py "release_GP1010AX.json" "cypress/cypress.env.json"
```

The script is located in `MC5000AX/i5g-fe/develop/e2e/cypress/integration/deploy`.

## Run docker container

Cypress can be used in GUI enabled mode or CLI mode.
Running the the container from base `/git` directory will allow cypress to access all the projects in your git directory.

### GUI mode

To run cypress in GUI enabled mode, run the following script from `/git` directory:

```bash
./cypress/scripts/docker_cnt_gui.sh
```

### CLI mode

To run cypress in CLI mode, run the following command(s) from `/git` directory:

```bash
docker run -d --name cypress --net host -w "${PWD}" -v "${PWD}:${PWD}" -u "$(id -u)" cypress:local sleep inf
docker exec -it cypress bash
```

This will make a docker container from the image we pulled before, run it in the background and enter the running container.
 
##	Run cypress test(s)

Always use the lastest `cypress.config.j`s and `cypress.env.json` files from project `MC5000AX_TOP` when running the test(s).

```bash
#The basic command syntax for starting cypress test.
cypress run -P <project_dir> -C <config> -b <browser> -s <spec>
# Run a cypress test with browser GUI.
cypress run -P "${PWD}" -C cypress.config.js -b chrome -s deploy-core.e2e.spec.js --headed
# Run a cypress test without browser GUI.
cypress run -P "${PWD}" -C cypress.config.js -b chrome -s deploy-core.e2e.spec.js
# Run cypress GUI editor.
cypress open -P "${PWD}"
```

## Stopping and restarting docker container

```bash
# Stop the running cypress docker container.
docker stop cypress
# Restart stopped docker container.
docker start cypress
# Reenter running container.
docker exec -it -u "$(id -u)" cypress bash
```
