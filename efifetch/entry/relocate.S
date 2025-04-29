.data
dummy0:	.4byte	0
dummy1:	.4byte	0

#define IMAGE_REL_ABSOLUTE 0
.section .reloc, "a", %progbits
.4byte	dummy1 - dummy0
.4byte	12
.2byte	(IMAGE_REL_ABSOLUTE<<12) + 0
.2byte	(IMAGE_REL_ABSOLUTE<<12) + 0
#if defined(__ELF__) && defined(__linux__)
.section .note.GNU-stack,"",%progbits
#endif
