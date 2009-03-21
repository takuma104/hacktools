#include <stdio.h>
#include <bfd.h>

int GetBFDSymbol(const char *fname)
{
	const int dyn = 0;
	int ret = 0;
	void *minisyms = 0;
	bfd *abfd = bfd_openr(fname, NULL);
	if (abfd == 0) return -1;
	if (bfd_check_format(abfd, bfd_object) == 0) {
		ret = -2;
		goto EXIT;
	}
	if (!(bfd_get_file_flags(abfd) & HAS_SYMS)) {
		ret = -3;
		goto EXIT;
	}
	{
		asymbol *store = bfd_make_empty_symbol(abfd);
		unsigned int size;
		int symnum = bfd_read_minisymbols(abfd, dyn, &minisyms, &size);
		if (symnum < 0) {
			ret = -4;
			goto EXIT;
		}
		char *p = (char*)minisyms;
		int i;
		for (i = 0; i < symnum; i++) {
			asymbol *sym = bfd_minisymbol_to_symbol(abfd, dyn, p, store);
			p += size;
			const char *name = bfd_asymbol_name(sym);
			if (name && *name == '.') continue;
			bfd_vma value = bfd_asymbol_value(sym);
			printf("%p %s\n", value, name);
		}
	}
EXIT:
	free(minisyms);
	bfd_close(abfd);
	return ret;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: addr2name executable\n");
		return -1;
	}
	GetBFDSymbol(argv[1]);
	return 0;
}

