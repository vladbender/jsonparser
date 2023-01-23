docker run \
  --rm \
  -it \
  -v `pwd`:/app \
  gcc:12.2.0 \
  sh -c "cd /app && ./build.sh && ./run.sh"