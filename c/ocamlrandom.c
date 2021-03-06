static int s[55] = {
  0x3ae2522b, 0x1d8d4634, 0x15b4fad0, 0x18b14ace, 0x12f8a3c4, 0x3b086c47,
  0x16d467d6, 0x101d91c7, 0x321df177, 0x0176c193, 0x1ff72bf1, 0x1e889109,
  0x0b464b18, 0x2b86b97c, 0x0891da48, 0x03137463, 0x085ac5a1, 0x15d61f2f,
  0x3bced359, 0x29c1c132, 0x3a86766e, 0x366d8c86, 0x1f5b6222, 0x3ce1b59f,
  0x2ebf78e1, 0x27cd1b86, 0x258f3dc3, 0x389a8194, 0x02e4c44c, 0x18c43f7d,
  0x0f6e534f, 0x1e7df359, 0x055d0b7e, 0x10e84e7e, 0x126198e4, 0x0e7722cb,
  0x1cbede28, 0x3391b964, 0x3d40e92a, 0x0c59933d, 0x0b8cd0b7, 0x24efff1c,
  0x2803fdaa, 0x08ebc72e, 0x0f522e32, 0x05398edc, 0x2144a04c, 0x0aef3cbd,
  0x01ad4719, 0x35b93cd6, 0x2a559d4f, 0x1e6fd768, 0x26e27f36, 0x186f18c3,
  0x2fbf967a,
};

static int idx = 0;

int bits() {
  idx = (idx + 1) % 55;
  int curval = s[idx];
  int newval = s[(idx + 24) % 55] + (curval ^ ((curval >> 25) & 0x1F));
  int newval30 = newval & 0x3FFFFFFF;
  s[idx] = newval30;
  return newval30;
}

