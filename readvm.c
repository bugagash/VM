//Instructions for VM

#define INSTRUCTIONS_NUM 18

enum {
	PUSH_CODE,
	POP_CODE,
	ADD_CODE,
	SUB_CODE,
	MUL_CODE,
	DIV_CODE,
	JMP_CODE, // always
	JL_CODE, // <
	JG_CODE, // >
	JE_CODE, // ==
	JNE_CODE, // !=
	STORE_CODE, // exactly where
	LOAD_CODE, // exactly from
	CALL_CODE, // procedure proging JMP to func and add addres
	RET_CODE, // last stack addres and lmp
	HLT_CODE, // Like exit
	LABEL_CODE, // psevdo :) ???
	COMMENT_CODE, // psevdo :) ???
	PASS_CODE,
};


const char* opcodelist[INSTRUCTIONS_NUM] = {
	[PUSH_CODE] = "push",
	[POP_CODE] = "pop",
	[ADD_CODE] = "add",
	[SUB_CODE] = "sub",
	[MUL_CODE] = "mul",
	[DIV_CODE] = "div",
	[JMP_CODE] = "jmp",
	[JL_CODE] = "jl",
	[JG_CODE] = "jg",
	[JE_CODE] = "je",
	[JNE_CODE] = "jne",
	[STORE_CODE] = "store",
	[LOAD_CODE] = "load"
	[CALL_CODE] = "call",
	[RET_CODE] = "ret",
	[HLT_CODE] = "hlt",
	[LABEL_CODE] = "label",
	[COMMENT_CODE] = ";",
}


extern int8_t readvm_src(FILE *output, FILE *input);
extern int32_t readvm_exc(FILE *input);


extern int8_t readvm_src(FILE *output, FILE *input) {
	
}

