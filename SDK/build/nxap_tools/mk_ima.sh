#!/bin/bash

#path info
current_path=`pwd`
shell_path=`dirname $0`
work_path=$shell_path"/../../id.kernel"
elf_name="zhuque"

#elf file
if [ -n "$1" ]; then
    product_out="$1"
fi
if [ -n "$product_out" ]; then
    elf_file="$product_out/$elf_name"
    bak_elf_file="$product_out/${elf_name}.noima"
else
    elf_file="$elf_name"
    bak_elf_file="${elf_name}.noima"
fi

#check elf file exist
function is_elf_exist()
{
    if [ ! -f "$elf_file" ]
    then
        echo $elf_file" does not exist!"
        return 1;
    fi

    return 0;
}

#remove file
function check_and_remove_file()
{
    if [ -f "$1" ]
    then
        rm "$1"
    fi
}

#after compiling, exec ima preconfig
function ima_preconfig()
{
    # section information
    section_name=(".text" ".rodata" ".data")
    section_position=(0 0 0)
    section_virtual_position=(0 0 0)
    section_length=(0 0 0)
    section_text_begin="_stext"
    section_text_begin_offset=0

    # hash information
    hash_start=("_stext_hash" "_srodata_hash")
    hash_position=(0 0)
    hash_virtual_position=(0 0)

    #section size
    section_size=3

    #section md5
    section_md5=("" "")

    #md5 length
    md5_len=128

    #align size
    align_size=4

    #max move size
    max_move_size=256

    #elf section info file
    elf_section_info_file="elf.section"

    #elf symbol file
    elf_symbol_file="elf.symbol"

    #temp section file
    temp_section_file="temp_section_file"
    temp_section_file1="temp_section_file1"
    temp_section_file2="temp_section_file2"
    temp_section_file3="temp_section_file3"

    check_and_remove_file $bak_elf_file

    #create elf noima
    cp "$elf_file" "$bak_elf_file"

    check_and_remove_file $elf_section_info_file
    check_and_remove_file $elf_symbol_file

    # read section info from elf file
    readelf -S "$elf_file" > "$elf_section_info_file"

    # read symbol from elf file
    readelf -rs "$elf_file" > "$elf_symbol_file"

    echo "calc section position and length"
    i=0
    while [ $i -lt $section_size ]
    do
        #get name of section
        s=${section_name[$i]}
        #echo $s

        check_result=`grep -w $s $elf_section_info_file`
        temp_str=${check_result:6}
        check_array=($temp_str)

        #section position
        section_position[$i]=$((16#${check_array[3]}))

        #section virtual position
        section_virtual_position[$i]=$((16#${check_array[2]}))

        #section size
        section_length[$i]=$((16#${check_array[4]}))

        let i++
    done

    check_and_remove_file $elf_section_info_file

    #correct sections' information
    #at the beginning of text section, there is a table which is changable.
    #we should compute section text's hash after the table.
    check_result=`grep -w $section_text_begin $elf_symbol_file`
    if [ -z "$check_result" ]
    then
        echo "symbol "$section_text_begin" does not exist!"
        check_and_remove_file $elf_symbol_file
        return 1
    fi

    check_array=($check_result)
    len=${#check_array}
    if [ $len -lt 2 ]
    then
        echo "check symbol "$section_text_begin" error!"
        check_and_remove_file $elf_symbol_file
        return 2
    fi

    section_text_begin_offset=$((16#${check_array[1]}-${section_virtual_position[0]}))

    section_virtual_position[0]=$((16#${check_array[1]}))
    section_position[0]=$((${section_position[0]}+$section_text_begin_offset))
    section_length[0]=$((${section_length[0]}-$section_text_begin_offset))

    # calc the position of hash
    echo "calc the postion of hash"
    data_section_address=${section_position[2]}
    data_section_virtual_address=${section_virtual_position[2]}

    i=0
    while [ $i -lt $(($section_size-1)) ]
    do
        s=${hash_start[$i]}
        #echo $s

        check_result=`grep -w $s $elf_symbol_file`
        if [ -z "$check_result" ]
        then
            echo "symbol "$s" does not exist!"
            check_and_remove_file $elf_symbol_file
            return 1
        fi

        check_array=($check_result)
        len=${#check_array}
        if [ $len -lt 2 ]
        then
            echo "check symbol "$s" error!"
            check_and_remove_file $elf_symbol_file
            return 2
        fi

        hash_virtual_position[$i]=${check_array[1]}
        hash_position[$i]=$((16#${check_array[1]}-$data_section_virtual_address+$data_section_address))

        let i++
    done

    check_and_remove_file $temp_section_file
    check_and_remove_file $temp_section_file1
    check_and_remove_file $temp_section_file2
    check_and_remove_file $temp_section_file3

    echo "calc md5..."
    i=0
    while [ $i -lt $(($section_size-1)) ]
    do
        #echo ${section_name[$i]}
        start_pos=${section_position[$i]}
        cur_section_len=${section_length[$i]}

        first_move_pos=$(($start_pos/$align_size))
        count_blocks=$((($max_move_size-$start_pos%$max_move_size)/$align_size))
        dd if=$elf_file bs=$align_size skip=$first_move_pos count=$count_blocks of=$temp_section_file1

        second_move_pos=$(($start_pos/$max_move_size+1));
        count_blocks=$((($cur_section_len-$count_blocks*$align_size)/$max_move_size))
        dd if=$elf_file bs=$max_move_size skip=$second_move_pos count=$count_blocks of=$temp_section_file2

        third_move_pos=$((($second_move_pos+$count_blocks)*$max_move_size/$align_size));
        count_blocks=$((($start_pos+$cur_section_len-$third_move_pos*$align_size)/$align_size))
        dd if=$elf_file bs=$align_size skip=$third_move_pos count=$count_blocks of=$temp_section_file3

        cat $temp_section_file1 $temp_section_file2 $temp_section_file3 > $temp_section_file

        rm "$temp_section_file1"
        rm "$temp_section_file2"
        rm "$temp_section_file3"

        md5_result=`md5sum $temp_section_file`
        md5_result_array=($md5_result)
        md5=${md5_result_array[0]}
        #echo $md5
        section_md5[$i]=$md5

        rm "$temp_section_file"

        let i++
    done

    echo "write md5 value to binary..."
    i=0
    while [ $i -lt $(($section_size-1)) ]
    do
        #write md5 value
        md5=${section_md5[$i]}

        hash_start_pos_blocks=$((${hash_position[$i]}/$align_size))
        hash_len=$(($md5_len/8/$align_size))

        echo $md5 | xxd -r -p | dd bs=$align_size seek=$hash_start_pos_blocks count=$hash_len conv=notrunc of=$elf_file

        let i++
    done

    check_and_remove_file $elf_symbol_file

    return 0
}

cd $shell_path
pushd $work_path > /dev/null

is_elf_exist
ret=$?
if [ $ret -eq 0 ]
then
    ima_preconfig
    ret=$?
    if [ $ret -ne 0 ]
    then
        cp "$bak_elf_file" "$elf_file"
        rm "$bak_elf_file"
        echo "ima preconfig failed!"
    else
        echo "ima preconfig successfully!"
    fi
else
    echo "ima preconfig failed!"
fi

popd > /dev/null
cd $current_path
