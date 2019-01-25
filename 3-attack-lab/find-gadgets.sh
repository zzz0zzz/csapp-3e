#!/bin/sh

# usage: $1 - path to rtarget

instructions=$(cat <<EndOfInstructions
4889c0;movq %rax,%rax;
4889c1;movq %rax,%rcx;
4889c2;movq %rax,%rdx;
4889c3;movq %rax,%rbx;
4889c4;movq %rax,%rsp;
4889c5;movq %rax,%rbp;
4889c6;movq %rax,%rsi;
4889c7;movq %rax,%rdi;
4889c8;movq %rcx,%rax;
4889c9;movq %rcx,%rcx;
4889ca;movq %rcx,%rdx;
4889cb;movq %rcx,%rbx;
4889cc;movq %rcx,%rsp;
4889cd;movq %rcx,%rbp;
4889ce;movq %rcx,%rsi;
4889cf;movq %rcx,%rdi;
4889d0;movq %rdx,%rax;
4889d1;movq %rdx,%rcx;
4889d2;movq %rdx,%rdx;
4889d3;movq %rdx,%rbx;
4889d4;movq %rdx,%rsp;
4889d5;movq %rdx,%rbp;
4889d6;movq %rdx,%rsi;
4889d7;movq %rdx,%rdi;
4889d8;movq %rbx,%rax;
4889d9;movq %rbx,%rcx;
4889da;movq %rbx,%rdx;
4889db;movq %rbx,%rbx;
4889dc;movq %rbx,%rsp;
4889dd;movq %rbx,%rbp;
4889de;movq %rbx,%rsi;
4889df;movq %rbx,%rdi;
4889e0;movq %rsp,%rax;
4889e1;movq %rsp,%rcx;
4889e2;movq %rsp,%rdx;
4889e3;movq %rsp,%rbx;
4889e4;movq %rsp,%rsp;
4889e5;movq %rsp,%rbp;
4889e6;movq %rsp,%rsi;
4889e7;movq %rsp,%rdi;
4889e8;movq %rbp,%rax;
4889e9;movq %rbp,%rcx;
4889ea;movq %rbp,%rdx;
4889eb;movq %rbp,%rbx;
4889ec;movq %rbp,%rsp;
4889ed;movq %rbp,%rbp;
4889ee;movq %rbp,%rsi;
4889ef;movq %rbp,%rdi;
4889f0;movq %rsi,%rax;
4889f1;movq %rsi,%rcx;
4889f2;movq %rsi,%rdx;
4889f3;movq %rsi,%rbx;
4889f4;movq %rsi,%rsp;
4889f5;movq %rsi,%rbp;
4889f6;movq %rsi,%rsi;
4889f7;movq %rsi,%rdi;
4889f8;movq %rdi,%rax;
4889f9;movq %rdi,%rcx;
4889fa;movq %rdi,%rdx;
4889fb;movq %rdi,%rbx;
4889fc;movq %rdi,%rsp;
4889fd;movq %rsi,%rbp;
4889fe;movq %rdi,%rsi;
4889ff;movq %rdi,%rdi;
89c0;movl %eax,%eax;
89c1;movl %eax,%ecx;
89c2;movl %eax,%edx;
89c3;movl %eax,%ebx;
89c4;movl %eax,%esp;
89c5;movl %eax,%ebp;
89c6;movl %eax,%esi;
89c7;movl %eax,%edi;
89c8;movl %ecx,%eax;
89c9;movl %ecx,%ecx;
89ca;movl %ecx,%edx;
89cb;movl %ecx,%ebx;
89cc;movl %ecx,%esp;
89cd;movl %ecx,%ebp;
89ce;movl %ecx,%esi;
89cf;movl %ecx,%edi;
89d0;movl %edx,%eax;
89d1;movl %edx,%ecx;
89d2;movl %edx,%edx;
89d3;movl %edx,%ebx;
89d4;movl %edx,%esp;
89d5;movl %edx,%ebp;
89d6;movl %edx,%esi;
89d7;movl %edx,%edi;
89d8;movl %ebx,%eax;
89d9;movl %ebx,%ecx;
89da;movl %ebx,%edx;
89db;movl %ebx,%ebx;
89dc;movl %ebx,%esp;
89dd;movl %ebx,%ebp;
89de;movl %ebx,%esi;
89df;movl %ebx,%edi;
89e0;movl %esp,%eax;
89e1;movl %esp,%ecx;
89e2;movl %esp,%edx;
89e3;movl %esp,%ebx;
89e4;movl %esp,%esp;
89e5;movl %esp,%ebp;
89e6;movl %esp,%esi;
89e7;movl %esp,%edi;
89e8;movl %ebp,%eax;
89e9;movl %ebp,%ecx;
89ea;movl %ebp,%edx;
89eb;movl %ebp,%ebx;
89ec;movl %ebp,%esp;
89ed;movl %ebp,%ebp;
89ee;movl %ebp,%esi;
89ef;movl %ebp,%edi;
89f0;movl %esi,%eax;
89f1;movl %esi,%ecx;
89f2;movl %esi,%edx;
89f3;movl %esi,%ebx;
89f4;movl %esi,%esp;
89f5;movl %esi,%ebp;
89f6;movl %esi,%esi;
89f7;movl %esi,%edi;
89f8;movl %edi,%eax;
89f9;movl %edi,%ecx;
89fa;movl %edi,%edx;
89fb;movl %edi,%ebx;
89fc;movl %edi,%esp;
89fd;movl %edi,%ebp;
89fe;movl %edi,%esi;
89ff;movl %edi,%edi;
58;popq %rax;
59;popq %rcx;
5a;popq %rdx;
5b;popq %rbx;
5c;popq %rsp;
5d;popq %rbp;
5e;popq %rsi;
5f;popq %rdi;
20c0;andb %al;
20c9;andb %cl;
20d2;andb %dl;
20db;andb %bl;
08c0;orb %al;
08c9;orb %cl;
08d2;orb %dl;
08db;orb %bl;
38c0;cmpb %al;
38c9;cmpb %cl;
38d2;cmpb %dl;
38db;cmpb %bl;
84c0;testb %al;
84c9;testb %cl;
84d2;testb %dl;
84db;testb %bl;
90;nop;
EndOfInstructions
)

instructions=$(echo $instructions | sed 's/; /;/g')

farm=$(objdump -d $1 \
    | grep -A1000 start_farm \
    | grep -B1000 end_farm \
    | head -n -1 \
    | sed '/^0000/d' \
    | sed '/^$/d' \
    | sed s/^.*:.// \
    | sed -n -e 's/  \+\x09.*//p' \
    | tr -d ' \n')

farm_start_address=$(printf '%d' 0x$(objdump -d $1 | grep start_farm | cut -d' ' -f1))

print_gadget() {
  local farm_length=${#farm}
  local last_gadget_index=$(echo $gadget_indexes | cut -d' ' -f1)
  local last_encoding=$(echo $instructions | cut -d';' -f$((2*last_gadget_index - 1)))
  local last_encoding_length=${#last_encoding}
  local last_instruction="$(echo $instructions | cut -d';' -f$((2*last_gadget_index)))"
  local gadget_address=$(printf '%x' $((farm_start_address + farm_length/2 - last_encoding_length/2)))
  local gadget=''
  local

  local i
  for i in $gadget_indexes; do
    gadget="$gadget$(echo $instructions | cut -d';' -f$((2*i))) | "
  done
  gadget="$gadget"retq
  echo "$gadget_address    $gadget"
}

print_gadgets() {
  local i=1
  while test $i -le 153; do
    local current_encoding=$(echo $instructions | cut -d';' -f$((2*i-1)))

    if test ${#farm} -lt ${#current_encoding} || 
       test ${farm%$current_encoding} = $farm; then
      i=$((i+1))
      continue;
    fi

    gadget_indexes="$i $gadget_indexes"
    print_gadget
    farm=${farm%$current_encoding}
    print_gadgets
    gadget_indexes=${gadget_indexes##* }
    farm=$farm"$current_encoding"
    
    i=$((i+1))
  done
}

print_all_gadgets() {
  echo 'Address   Gadget'
  echo '=======   ======'
  while test ${farm#*c3} != $farm; do
    farm=${farm%c3*}
    print_gadgets
  done
}

print_all_gadgets
