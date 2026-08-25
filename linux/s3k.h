
// Stuff added for s3k
#define S3K_EID 0x0A53334B

// s3k_debug_print_dummy,
// s3k_plic_toggle,
// s3k_plic_mask,
// s3k_irq_complete,
// s3k_get_irq_priority,
// s3k_set_irq_priority,
// s3k_get_claim,
// BIG BUG: hwirq is unsigned LONG
static inline int sbi_print_debug(void)
{
	// TODO: contains ret val from sbi
	register int a0 __asm__("a0");
	register int a7 __asm__("a7") = S3K_EID;
	register int a6 __asm__("a6") = 0;
	__asm__ volatile("ecall" : "+r"(a0) : "r"(a6) , "r"(a7));
	return a0;
}

static inline uint64_t s3k_plic_toggle(uint32_t hwirq, uint32_t val)
{
	// TODO: contains ret val from sbi
	register int a0 __asm__("a0") = hwirq;
	register int a1 __asm__("a1") = val;
	register int a7 __asm__("a7") = S3K_EID;
	register int a6 __asm__("a6") = 1;
	__asm__ volatile("ecall" : "+r"(a0) ,"+r"(a1) : "r"(a0) , "r"(a6) , "r"(a7));
	return a1;
}

// static inline uint64_t s3k_get_plic_enabled_srcs(void)
// {
// 	// TODO: contains ret val from sbi
// 	register int a0 __asm__("a0");
// 	register int a1 __asm__("a1");
// 	register int a7 __asm__("a7") = S3K_EID;
// 	register int a6 __asm__("a6") = 2;
// 	__asm__ volatile("ecall" : "+r"(a0) , "+r"(a1) : "r"(a6) , "r"(a7));
// 	return a1;
// }

static inline uint64_t s3k_plic_mask(uint32_t hwirq, uint32_t val)
{
	// TODO: contains ret val from sbi
	register int a0 __asm__("a0") = val;
	register int a1 __asm__("a1") = hwirq;
	register int a7 __asm__("a7") = S3K_EID;
	register int a6 __asm__("a6") = 2;
	__asm__ volatile("ecall" : "+r"(a0) ,"+r"(a1) : "r"(a0), "r"(a1) , "r"(a6) , "r"(a7));
	return a1;
}

static inline uint64_t s3k_plic_complete(uint32_t hwirq)
{
	// TODO: contains ret val from sbi
	register int a0 __asm__("a0") = hwirq;
	register int a1 __asm__("a1");
	register int a7 __asm__("a7") = S3K_EID;
	register int a6 __asm__("a6") = 3;
	__asm__ volatile("ecall" : "+r"(a0) ,"+r"(a1) : "r"(a0), "r"(a6) , "r"(a7));
	return a1;
}

static inline uint32_t s3k_get_irq_priority(uint32_t val)
{
	// TODO: contains ret val from sbi
	register int a0 __asm__("a0") = val;
	register int a1 __asm__("a1");
	register int a7 __asm__("a7") = S3K_EID;
	register int a6 __asm__("a6") = 4;
	__asm__ volatile("ecall" : "+r"(a0) ,"+r"(a1) : "r"(a0), "r"(a6) , "r"(a7));
	return a1;
}

static inline uint64_t s3k_set_irq_prio(uint32_t hwirq, uint32_t val)
{
	// TODO: contains ret val from sbi
	register int a0 __asm__("a0") = hwirq;
	register int a1 __asm__("a1") = val;
	register int a7 __asm__("a7") = S3K_EID;
	register int a6 __asm__("a6") = 5;
	__asm__ volatile("ecall" : "+r"(a0) ,"+r"(a1) : "r"(a0), "r"(a1) , "r"(a6) , "r"(a7));
	return a1;
}

// static inline uint32_t s3k_enable_intr(uint32_t val, uint32_t idx)
// {
// 	// TODO: contains ret val from sbi
// 	register int a0 __asm__("a0") = val;
// 	register int a1 __asm__("a1") = idx;
// 	register int a7 __asm__("a7") = S3K_EID;
// 	register int a6 __asm__("a6") = 6;
// 	__asm__ volatile("ecall" : "+r"(a0) ,"+r"(a1) : "r"(a0), "r"(a6) , "r"(a7));
// 	return a1;
// }

static inline uint32_t s3k_get_claim(void)
{
	// TODO: contains ret val from sbi
	register int a0 __asm__("a0");
	register int a1 __asm__("a1");
	register int a7 __asm__("a7") = S3K_EID;
	register int a6 __asm__("a6") = 6;
	__asm__ volatile("ecall" : "+r"(a0) ,"+r"(a1) : "r"(a6) , "r"(a7));
	return a1;
}

static inline uint64_t s3k_set_threshold(uint32_t val)
{
	// TODO: contains ret val from sbi
	register int a0 __asm__("a0") = val;
	register int a1 __asm__("a1");
	register int a7 __asm__("a7") = S3K_EID;
	register int a6 __asm__("a6") = 7;
	__asm__ volatile("ecall" : "+r"(a0) ,"+r"(a1) : "r"(a0), "r"(a6) , "r"(a7));
	return a1;
}
