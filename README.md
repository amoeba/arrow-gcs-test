# arrow-gcs-test

Using [Apache Arrow](https://arrow.apache.org)'s Google Cloud Storage API.

## Building and Running

- Compile and install Apache Arrow C++ and make available at $ARROW_HOME
    - Must include ARROW_FILEYSTEM=ON, ARROW_GCS=ON
- cmake . && cmake --build .
- ./test-gcs
