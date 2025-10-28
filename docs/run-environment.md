# Running the GeMSE Docker Environment

The **GeMSE_environment** repository provides a fully reproducible software environment for GeMSE analysis and simulations. It includes **Miniconda**, **ROOT**, **BAT (Bayesian Analysis Toolkit)**, and **Geant4**, all pre-installed and configured.

---

## 1. Using Docker (recommended for macOS)

If Docker is available on your machine, you can either **build the image locally** or **pull the prebuilt image from DockerHub**.

List existing images:

```bash
docker images
```

---

### A) Pull prebuilt image from DockerHub

A prebuilt version of the container is available at:
→ [DockerHub](https://hub.docker.com/r/ramirezdiego/gemse_env)

You can download it directly:

```bash
docker pull ramirezdiego/gemse_env:latest
```

Once downloaded, start an  container session:

```bash
docker run -it --rm \
  -v "$PWD":/work \
  -w /work \
  ramirezdiego/gemse_env:latest \
  /bin/bash
```

This command:
- runs the GeMSE environment interactively (`-it`)
- removes the container when you exit (`--rm`)
- mounts your current working directory inside the container (`-v "$PWD":/work`)
- sets `/work` as the default working directory (`-w /work`)

You will now be inside the GeMSE analysis environment, ready to use ROOT, Geant4, and BAT.


For graphical support, use this command instead:
 - For Linux systems: Open X11  access for local Docker containers:

```bash
xhost +local:docker
```
Then run:
```bash
docker run -it --rm \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v "$PWD":/work \
  -w /work \
  ramirezdiego/gemse_env:latest \
  /bin/bash
```

 
  - For macOS with XQuartz: Make sure "Allow connections from network clients" is enabled in XQuartz preferences.

```bash
brew install --cask xquartz # if not already installed
xhost + 127.0.0.1
``` 
Then run:
```bash
docker run -it --rm \
  -e DISPLAY=host.docker.internal:0 \
  -v "$PWD":/work \
  -w /work \
  ramirezdiego/gemse_env:latest \
  /bin/bash
```

Additionally,
```bash 
docker run -it --rm \
  --name g4 \
  -e DISPLAY=host.docker.internal:0 \
  -e LIBGL_ALWAYS_INDIRECT=1 \
  -e MESA_GL_VERSION_OVERRIDE=3.3 \
  -e MESA_GLSL_VERSION_OVERRIDE=330 \
  -v "$PWD":/work \
  -w /work \
  ramirezdiego/gemse_env:latest \
  /bin/bash

```

- now you can use ROOT with graphical support inside the container.
```bash
root -l
root [0] TBrowser b;
```




---

### B) Build the image locally

If you prefer to build it yourself:

```bash
git clone https://github.com/AG-Schumann/GeMSE_environment.git
cd GeMSE_environment
docker build -t <CONTAINER_NAME> .
```

Run the locally built image:

```bash
docker run -it --rm \
  -v "$PWD":/work \
  -w /work \
  <CONTAINER_NAME> \
  /bin/bash
```

---

**Tip:** If you need graphical ROOT (X11) support, add the following flags:

```bash
-e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix
```

This enables ROOT's GUI and interactive canvases on your host system.

---

## 2. Using Singularity / Apptainer (for regular usage)

Some scripts are especially written for Singularity usage. For regular Linux users, it is recommended to use Singularity/Apptainer instead of Docker.

### Option A: Build from Docker Hub

If the image is available on DockerHub (e.g. *ramirezdiego/gemse_env:latest*), run:

```bash
singularity build --tmpdir ~/Desktop/ gemse_env.sif docker://ramirezdiego/gemse_env:latest
```

This command **automatically pulls** the Docker image from DockerHub and converts it into a Singularity image (`.sif` file). No manual `docker pull` is required.

The `--tmpdir` argument specifies a temporary directory with enough free space during the build process.

Then, launch an interactive shell:

```bash
singularity shell gemse_env.sif
```

---

### Option B: Build from a local Docker image

If you built the Docker image locally and do not wish to upload it to DockerHub, you can still convert it manually.

**Method 1 – Using docker-archive:**

```bash
docker build -t gemse_env:local .
docker save gemse_env:local -o gemse_env.tar
singularity build gemse_env.sif docker-archive://$(pwd)/gemse_env.tar
```

**Method 2 – Using oci-archive (if supported):**

```bash
docker build -t gemse_env:local .
skopeo copy docker-daemon:gemse_env:local oci-archive:gemse_env_oci.tar:gemse_env_local
singularity build gemse_env.sif oci-archive://$(pwd)/gemse_env_oci.tar
```

Both methods produce a single, portable `gemse_env.sif` file equivalent to the Docker image.

---

## 3. Working with the GeMSE Environment
Once inside the container (via Docker or Singularity), ROOT, Geant4, and BAT must be set up by sourcing the appropriate scripts:

For Analysis tools (ROOT + BAT):
```bash
source /opt/GeMSE/setup.sh
``` 

For Simulation tools (Geant4):
```bash
source /opt/GeMSE/geant4_setup.sh
```

This configures the environment variables and paths for the installed software.

### Example: Processing a GeMSE Measurement to Root File

```bash
source /opt/GeMSE/setup.sh
g++ process_GeMSE_data.cxx -o process_GeMSE_data $(root-config --cflags --libs) -lMinuit
```
or 
```bash
g++ ../energy_resolution.cxx -o energy_resolution \
    $(root-config --cflags) -O2 -std=c++17 \
    $(root-config --libs) -lMinuit
```

Then run:
```bash
./process_GeMSE_data input_data.txt 
```
