#include <stdio.h>
#include <stdint.h>
#include <string.h>


uint8_t memory[65536];
uint16_t sp = 0;

void display() {
	
}

int main(int argc, char *argv[]) {
	char *env = "PATH=/usr;/usr/bin";
	uint16_t len = 0;
	int i, j, ai;
	uint16_t si;
	uint16_t env_head;
	uint16_t env_len = strlen(env);

	uint16_t argaddrs[10]; 
	
	len = env_len;
	len++;
	
	for (i = 0; i < argc; ++i) {
		len += strlen(argv[i]);
		len++;
	}
	
	// padding
	if (len % 2) memory[--sp] = 0;
	
	// 環境変数を積む
	for (i = env_len; i >= 0; --i) {
		memory[--sp] = env[i];
		//		printf("%d = %c\n", i, env[i]);
	}
	env_head = sp;

	// 引数を積む
	for (ai = 0, i = (argc-1); i >= 0; --i, ++ai) {
		for (j = strlen(argv[i]); j >= 0; --j) {
			memory[--sp] = argv[i][j];
		}
		argaddrs[ai] = sp;		
	}

	// 区切り
	memory[--sp] = 0;
	memory[--sp] = 0;

	// envのアドレスを積む
	memory[--sp] = env_head >> 8;
	memory[--sp] = env_head;

	//	printf("env_head = %04x\n", env_head);

	// 区切り
	memory[--sp] = 0;
	memory[--sp] = 0;
	
	for(i = 0; i < argc; ++i) {
		memory[--sp] = argaddrs[i] >> 8;
		memory[--sp] = argaddrs[i];
	}

	memory[--sp] = argc >> 8;
	memory[--sp] = argc;

	

	for (si = sp; si != 0; ++si) {
		if ((memory[si] > 0x20) && (memory[si] < 0x7f)) {
			printf("[%04x]:%c\n", si, memory[si]);
		} else {
			printf("[%04x]:%02x\n", si, memory[si]);
		}
	}

	//	printf("sp = %04x\n", sp);

	
	return 0;
}
