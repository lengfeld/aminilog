# SPDX-License-Identifier: MIT
# SPDX-FileCopyrightText: (c) 2022 Stefan Lengfeld

all:
	@echo Execute \'make help\' for details!

# TODO Maybe get architecture from env. Currently it's hardcoded to x86_64.
BINARY_SDK = sdk-app/app/build/intermediates/cmake/debug/obj/x86_64/aminilogtest
BINARY_AOSP = ${ANDROID_PRODUCT_OUT}/system/bin/aminilogtest

.PHONY: build-sdk
build-sdk:   ## Build the test binary with the SDK
	cd sdk-app && ./gradlew externalNativeBuildDebug

.PHONY: run-sdk
run-sdk:    ## Run the SDK test binary
	./run.sh ${BINARY_SDK}

.PHONY: clean-sdk
clean-sdk:   ## Clean SDK build
	cd sdk-app && ./gradlew clean


.PHONY: build-aosp
build-aosp: SHELL=/bin/bash  # Otherwise the AOSP build system does not work.
build-aosp:   ## Build the test binary with the AOSP
	source ${ANDROID_BUILD_TOP}/build/envsetup.sh && lunch ${TARGET_PRODUCT} && m aminilogtest

.PHONY: run-aosp
run-aosp:  ## Run the AOSP test binary
	./run.sh ${BINARY_AOSP}

.PHONY: clean-aosp
clean-aosp: SHELL=/bin/bash  # Otherwise the AOSP build system does not work.
clean-aosp:  ## Clean the AOSP build
	source ${ANDROID_BUILD_TOP}/build/envsetup.sh && lunch ${TARGET_PRODUCT} && m clean-aminilogtest

.PHONY: test
test:    ## Run test.py for the AOSP and the SDK binary
	./test.py ${BINARY_AOSP}
	./test.py ${BINARY_SDK}


.PHONY: help
help:  ## Show this message
	@sed -rn 's/^([a-zA-Z_-]+):.*?## (.*)$$/"\1" "\2"/p' < ${MAKEFILE_LIST} | xargs printf "make %-20s# %s\n"
