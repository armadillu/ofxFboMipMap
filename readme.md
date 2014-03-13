This allows you to use ofFbo's that generate/update their mipmaps transparently. you only need to call allocateWithMipMaps(ofFbo::Settings s) instead of allocate(ofFbo::Settings s) at allocation time.

This requires a tiny patch to ofTexture that allows for mipmaps to work, see it here. The patch is to be appplied to the OF_008 release

https://github.com/armadillu/openFrameworks/commit/03a1752b49306659c77f91c7d07b896e85200665

