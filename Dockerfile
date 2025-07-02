FROM debian:bullseye-slim

# Install dependencies
RUN apt-get update && apt-get install -y \
    wget \
    git \
    build-essential \
    python3 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Install devkitPro pacman
RUN wget https://apt.devkitpro.org/install-devkitpro-pacman && \
    chmod +x install-devkitpro-pacman && \
    ./install-devkitpro-pacman

# Install devkitARM and gba-dev
RUN dkp-pacman -Syu --noconfirm && \
    dkp-pacman -S --noconfirm devkitARM gba-dev

# Set environment variables for devkitARM
ENV DEVKITPRO=/opt/devkitpro
ENV DEVKITARM=/opt/devkitpro/devkitARM
ENV PATH=$DEVKITPRO/tools/bin:$PATH

WORKDIR /src

# Copy source
COPY . .

# (Optional) clone Butano submodule if not present
RUN git submodule update --init

# Build the ROM
RUN make -j$(nproc)