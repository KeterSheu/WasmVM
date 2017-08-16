#include <Decoder.h>

void Decoder::decode(Store &store, Stack &coreStack){
    std::vector<char> &funcBody = store.funcs.at(coreStack.curLabel->funcIdx)->code.body;
    char bincode = funcBody.at((coreStack.curLabel->instrOffset));
    coreStack.curLabel->instrOffset += 1;
    switch(bincode){
        case OP_Ctrl_unreachable:
            Instruction::ctrl_unreachable(store, coreStack);
        break;
        case OP_Ctrl_nop:
        break;
        case OP_Ctrl_block:
            Instruction::ctrl_block(funcBody, coreStack, funcBody.at(coreStack.curLabel->instrOffset++));
        break;
        case OP_Ctrl_loop:
            Instruction::ctrl_loop(coreStack, funcBody.at(coreStack.curLabel->instrOffset++));
        break;
        case OP_Ctrl_if:
            Instruction::ctrl_if(funcBody, coreStack, funcBody.at(coreStack.curLabel->instrOffset++));
        break;
        case OP_Ctrl_else:
            Instruction::ctrl_else(coreStack);
        break;
        case OP_Ctrl_end:
            Instruction::ctrl_end(coreStack);
        break;
        case OP_Ctrl_br:
            try{
                Instruction::ctrl_br(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset), coreStack);
            }catch(const char *e){
                throw Exception(std::string("[br] ") + e, coreStack);
            }
        break;
        case OP_Ctrl_br_if:
            try{
                Instruction::ctrl_br_if(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset), coreStack);
            }catch(const char *e){
                throw Exception(std::string("[br_if] ") + e, coreStack);
            }
        break;
        case OP_Ctrl_br_table:
            try{
                std::uint32_t targetSize = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::vector<std::uint32_t> depths;
                while(targetSize-- > 0){
                    depths.push_back(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset));
                }
                depths.push_back(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset));
                Instruction::ctrl_br_table(depths, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[br_table] ") + e, coreStack);
            }
        break;
        case OP_Ctrl_return:
            Instruction::ctrl_return(coreStack);
        break;
        case OP_Ctrl_call:
            try{
                Instruction::ctrl_call(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset), store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[call] ") + e, coreStack);
            }
        break;
        case OP_Ctrl_call_indirect:
            try{
                Instruction::ctrl_call_indirect(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset), store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[call_indirect] ") + e, coreStack);
            }
        break;
        case OP_i32_load:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i32_load(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i32.load] ") + e, coreStack);
            }
        break;
        case OP_i64_load:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_load(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.load] ") + e, coreStack);
            }
        break;
        case OP_f32_load:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::f32_load(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[f32.load] ") + e, coreStack);
            }
        break;
        case OP_f64_load:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::f64_load(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[f64.load] ") + e, coreStack);
            }
        break;
        case OP_i32_load8_s:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i32_load8_s(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i32.load8_s] ") + e, coreStack);
            }
        break;
        case OP_i32_load8_u:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i32_load8_u(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i32.load8_u] ") + e, coreStack);
            }
        break;
        case OP_i32_load16_s:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i32_load16_s(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i32.load16_s] ") + e, coreStack);
            }
        break;
        case OP_i32_load16_u:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i32_load16_u(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i32.load16_u] ") + e, coreStack);
            }
        break;
        case OP_i64_load8_s:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_load8_s(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.load8_s] ") + e, coreStack);
            }
        break;
        case OP_i64_load8_u:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_load8_u(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.load8_u] ") + e, coreStack);
            }
        break;
        case OP_i64_load16_s:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_load16_s(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.load16_s] ") + e, coreStack);
            }
        break;
        case OP_i64_load16_u:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_load16_u(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.load16_u] ") + e, coreStack);
            }
        break;
        case OP_i64_load32_s:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_load32_s(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.load32_s] ") + e, coreStack);
            }
        break;
        case OP_i64_load32_u:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_load32_u(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.load32_u] ") + e, coreStack);
            }
        break;
        case OP_i32_store:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i32_store(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i32.store] ") + e, coreStack);
            }
        break;
        case OP_i64_store:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_store(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.store] ") + e, coreStack);
            }
        break;
        case OP_f32_store:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::f32_store(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[f32.store] ") + e, coreStack);
            }
        break;
        case OP_f64_store:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::f64_store(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[f64.store] ") + e, coreStack);
            }
        break;
        case OP_i32_store8:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i32_store8(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i32.store8] ") + e, coreStack);
            }
        break;
        case OP_i32_store16:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i32_store16(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i32.store16] ") + e, coreStack);
            }
        break;
        case OP_i64_store8:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_store8(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.store8] ") + e, coreStack);
            }
        break;
        case OP_i64_store16:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_store16(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.store16] ") + e, coreStack);
            }
        break;
        case OP_i64_store32:
            try{
                std::int32_t align = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                std::int32_t offset = Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset);
                Instruction::i64_store32(align, offset, store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[i64.store32] ") + e, coreStack);
            }
        break;
        case OP_Current_memory:
            Instruction::current_memory(store, coreStack);
        break;
        case OP_Grow_memory:
            Instruction::grow_memory(store, coreStack);
        break;
        case OP_Drop:
            Instruction::drop(coreStack);
        break;
        case OP_Select:
            Instruction::select(coreStack);
        break;
        case OP_Get_local:
            try{
                Instruction::get_local(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset), coreStack);
            }catch(const char *e){
                throw Exception(std::string("[get_local] ") + e, coreStack);
            }
        break;
        case OP_Set_local:
            try{
                Instruction::set_local(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset), coreStack);
            }catch(const char *e){
                throw Exception(std::string("[set_local] ") + e, coreStack);
            }
        break;
        case OP_Tee_local:
            try{
                Instruction::tee_local(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset), coreStack);
            }catch(const char *e){
                throw Exception(std::string("[tee_local] ") + e, coreStack);
            }
        break;
        case OP_Get_global:
            try{
                Instruction::get_global(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset), store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[get_global] ") + e, coreStack);
            }
        break;
        case OP_Set_global:
            try{
                Instruction::set_global(Util::getLeb128_u32(funcBody, coreStack.curLabel->instrOffset), store, coreStack);
            }catch(const char *e){
                throw Exception(std::string("[set_global] ") + e, coreStack);
            }
        break;
        case OP_i32_const:
            try{
                Instruction::i32_const(coreStack, Util::getLeb128_i32(funcBody, coreStack.curLabel->instrOffset));
            }catch(const char *e){
                throw Exception(std::string("[i32.const] ") + e, coreStack);
            }
        break;
        case OP_i64_const:
            try{
                Instruction::i64_const(coreStack, Util::getLeb128_i64(funcBody, coreStack.curLabel->instrOffset));
            }catch(const char *e){
                throw Exception(std::string("[i64.const] ") + e, coreStack);
            }
        break;
        case OP_f32_const:
            try{
                Instruction::f32_const(coreStack, Util::getIEEE754_f32(funcBody, coreStack.curLabel->instrOffset));
            }catch(const char *e){
                throw Exception(std::string("[f32.const] ") + e, coreStack);
            }
        break;
        case OP_f64_const:
            try{
                Instruction::f64_const(coreStack, Util::getIEEE754_f64(funcBody, coreStack.curLabel->instrOffset));
            }catch(const char *e){
                throw Exception(std::string("[f64.const] ") + e, coreStack);
            }
        break;
        default:
        {
            char codeChr[2];
            sprintf(codeChr, "%02x", ((std::uint32_t)bincode) & 0xff);
#ifdef NDEBUG
            throw Exception(std::string("Unknown code: 0x") + codeChr, coreStack);
#else
            std::cout << Exception(std::string("Code: 0x") + codeChr, coreStack).desc << std::endl;
#endif
        }
        break;
    }
}