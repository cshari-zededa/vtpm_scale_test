#There are four parts:
# a) building tpm2-tss
# b) building tpm2-tools
# c) building the vtpm server from local source
# d) extracting only required bits from tpm2-tss and tpm2-tools
#    and the server

#Build TPM2-TSS and TPM2-TOOLS
FROM alpine:3.8 as build
RUN apk add --no-cache linux-headers=4.4.6-r2 git=2.18.2-r0 \
                          gcc=6.4.0-r9 g++=6.4.0-r9 autoconf=2.69-r2 \
                          automake=1.16.1-r0 libtool=2.4.6-r5 \
                          doxygen=1.8.14-r0 make=4.2.1-r2 \
                          openssl-dev=1.0.2t-r0 protobuf-dev=3.5.2-r0

#The vTPM server
COPY ./ /vtpm_server
WORKDIR /vtpm_server
RUN make clean && make all

COPY ./client /vtpm_client
WORKDIR /vtpm_client
RUN cp proto/api.proto .
RUN protoc --cpp_out=cpp api.proto
RUN make clean && make all

COPY test /test
WORKDIR /test
RUN g++ -g move.cpp -o move

#Pull a selected set of artifacts into the final stage.
FROM alpine:3.8
RUN apk add --no-cache openssl=1.0.2t-r0 protobuf=3.5.2-r0

COPY --from=build /vtpm_server/vtpm_server /usr/bin/
COPY --from=build /vtpm_client/eve_run /usr/bin/
COPY --from=build /vtpm_client/libevetools* /usr/lib/
COPY --from=build /test/move /usr/bin/
ENTRYPOINT []
WORKDIR /
