FROM devkitpro/devkitarm:latest

WORKDIR /edh-artifact-tracker-gba

# Copy source
COPY . .

# (Optional) clone Butano submodule if not present
RUN git submodule update --init

RUN ./docker-build.sh