#include <cstring>
#include "inst_internal.h"

/* ImmNoneInst  */
ImmNoneInst::ImmNoneInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
                          : InstBase(opcode) { }


/* ImmBlocktInst  */
ImmBlocktInst::ImmBlocktInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  int64_t value_type = RD_I64();
  if (value_type >= 0) {
    ERR("Block type: %ld\n", value_type);
    throw std::runtime_error("Block type with type section index unsupported!");
  }
  this->type = value_type;
}


/* ImmLabelInst  */
ImmLabelInst::ImmLabelInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->idx = RD_U32();  
}


/* ImmLabelsInst  */
ImmLabelsInst::ImmLabelsInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  uint32_t num_labels = RD_U32();
  for (uint32_t i = 0; i < num_labels; i++) {
    this->idxs.push_back(RD_U32());
  }
  this->def_idx = RD_U32();
}


/* ImmFuncInst  */
ImmFuncInst::ImmFuncInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->func = module.getFunc (RD_U32());
}


/* ImmSigTableInst  */
ImmSigTableInst::ImmSigTableInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->sig = module.getSig (RD_U32());
  this->table = module.getTable (RD_U32());
}


/* ImmLocalInst  */
ImmLocalInst::ImmLocalInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->idx = RD_U32();
}


/* ImmGlobalInst  */
ImmGlobalInst::ImmGlobalInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->global = module.getGlobal (RD_U32());
}


/* ImmTableInst  */
ImmTableInst::ImmTableInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->table = module.getTable (RD_U32());
}


/* ImmMemargInst  */
ImmMemargInst::ImmMemargInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  uint32_t align = RD_U32();
  bool has_memidx = ((align >> 6) & 1);
  this->align = (align & 0x3f);
  this->mem = module.getMemory (has_memidx ? (RD_U32()) : 0);
  this->offset = RD_U32();
}


/* ImmI32Inst  */
ImmI32Inst::ImmI32Inst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->value = RD_I32();
}


/* ImmF64Inst  */
ImmF64Inst::ImmF64Inst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  uint64_t rawbits = RD_U64_RAW();
  memcpy(&this->value, &rawbits, sizeof(double));
}


/* ImmMemoryInst  */
ImmMemoryInst::ImmMemoryInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->mem = module.getMemory (RD_U32());
}


/* ImmTagInst: UNIMPLEMENTED  */
ImmTagInst::ImmTagInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) { 
  throw std::runtime_error ("Unimplemeted TAG opcode"); 
}


/* ImmI64Inst  */
ImmI64Inst::ImmI64Inst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->value = RD_I64();
}


/* ImmF32Inst  */
ImmF32Inst::ImmF32Inst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  uint32_t rawbits = RD_U32_RAW();
  memcpy(&this->value, &rawbits, sizeof(float));
}


/* ImmRefnulltInst  */
ImmRefnulltInst::ImmRefnulltInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  wasm_type_t type = (wasm_type_t) RD_BYTE();
  if (!isReftype(type)) {
    throw std::runtime_error("RefNull instruction must take a reftype\n");
  }
  this->type = (wasm_type_t) type;
}


/* ImmValtsInst  */
ImmValtsInst::ImmValtsInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  uint32_t num_vals = RD_U32();
  for (uint32_t i = 0; i < num_vals; i++) {
    wasm_type_t type = (wasm_type_t) RD_BYTE();
    this->types.push_back(type);
  }
}


/* ImmDataMemoryInst  */
ImmDataMemoryInst::ImmDataMemoryInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->data = module.getData (RD_U32());
  this->mem = module.getMemory (RD_U32());
}


/* ImmDataInst  */
ImmDataInst::ImmDataInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->data = module.getData (RD_U32());
}


/* ImmMemorycpInst  */
ImmMemorycpInst::ImmMemorycpInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->dst = module.getMemory (RD_U32());
  this->src = module.getMemory (RD_U32());
}





/* ImmDataTableInst  */
ImmDataTableInst::ImmDataTableInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->data = module.getData (RD_U32());
  this->table = module.getTable (RD_U32());
}


/* ImmTablecpInst  */
ImmTablecpInst::ImmTablecpInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->dst = module.getTable (RD_U32());
  this->src = module.getTable (RD_U32());
}


/* ImmV128Inst  */
ImmV128Inst::ImmV128Inst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->value.v[0] = RD_U64_RAW();
  this->value.v[1] = RD_U64_RAW();
}


/* ImmLaneidxInst  */
ImmLaneidxInst::ImmLaneidxInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  this->idx = RD_BYTE();
}


/* ImmLaneidx16Inst  */
ImmLaneidx16Inst::ImmLaneidx16Inst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  for (int i = 0; i < 16; i++) {
    this->idxs.l[i] = RD_BYTE();
  }
}


/* ImmMemargLaneidxInst  */
ImmMemargLaneidxInst::ImmMemargLaneidxInst (WasmModule &module, Opcode_t opcode, buffer_t &buf)
    : InstBase(opcode) {
  uint32_t align = RD_U32();
  bool has_memidx = ((align >> 6) & 1);
  this->align = (align & 0x3f);
  this->mem = module.getMemory (has_memidx ? (RD_U32()) : 0);
  this->offset = RD_U32();
  this->laneidx = RD_BYTE();
}

