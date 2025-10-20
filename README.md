# GeMSE_environment

Docker software environment for GeMSE analysis and simulations.

Among other libraries and packages, it includes:
+ [miniconda](https://docs.conda.io/en/latest/miniconda.html)
+ [ROOT](https://root.cern/)
+ [BAT](https://bat.mpp.mpg.de/)
+ [Geant4](https://geant4.web.cern.ch/)


## Generate Docker container

There is an [automatic workflow](https://github.com/AG-Schumann/GeMSE_environment/tree/master/.github/workflows) in charge of building the container and uploading it to the [DockerHub](https://hub.docker.com/) after each commit to master branch. For the moment under [Diego's profile](https://hub.docker.com/u/ramirezdiego).

If you want to build this container locally, [install Docker](https://docs.docker.com/engine/install/) and run

```
git clone https://github.com/AG-Schumann/GeMSE_environment.git
cd GeMSE_environment
docker build -t <CONTAINER_NAME> .
```

where `<CONTAINER_NAME>` can optionally be `<CONTAINER_NAME>:<TAG>` (otherwise a default tag is assigned that can afterwards be changed). 

## Convert container into a Singularity image

This works only for containers already uploaded in the [DockerHub](https://hub.docker.com/).

[Install Singularity](https://sylabs.io/guides/3.3/user-guide/installation.html) and run

```
singularity build <SINGULARITY_IMAGE_NAME>.simg docker://<ORGANIZATION>/<CONTAINER_NAME>:<TAG>
```

Singularity uses a temporary directory to build the squashfs filesystem, and this temp space needs to be large enough to hold the entire resulting Singularity image. By default this happens in `/tmp`. If errors related to the insufficient build space arise, the argument `--tmpdir` serves to reassign this temporary directory.

An example command:
```
singularity build --tmpdir ~/Desktop/ gemse_env.simg docker://ramirezdiego/gemse_env:latest
```

To load the built image, just execute:
```
singularity shell <SINGULARITY_IMAGE_NAME>.simg
```
and enjoy GeMSE analysis.
