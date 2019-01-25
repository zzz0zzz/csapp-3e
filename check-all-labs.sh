#!/bin/sh

check_lab_1() {
    mkdir tmp
    wget http://csapp.cs.cmu.edu/3e/datalab-handout.tar --directory-prefix tmp --quiet
    tar -xf tmp/datalab-handout.tar --directory tmp
    wget https://github.com/zzz0zzz/csapp-3e/raw/master/1-data-lab/bits.c --output-document tmp/datalab-handout/bits.c --quiet
    make btest --directory tmp/datalab-handout --quiet
    echo Data Lab
    echo ========
    
    ./tmp/datalab-handout/btest -g | grep -q 36/36
    if test $?
        then echo 'Lab is OK.'
        else echo 'Lab is not OK.'
    fi
    
    echo
    rm -r tmp
}

check_lab_2() {
    mkdir tmp
    wget http://csapp.cs.cmu.edu/3e/bomb.tar --directory-prefix tmp --quiet
    tar -xf tmp/bomb.tar --directory tmp
    wget https://github.com/zzz0zzz/csapp-3e/raw/master/2-bomb-lab/solution.txt --directory-prefix tmp --quiet
    echo Bomb Lab
    echo ========

    ./tmp/bomb/bomb < tmp/solution.txt | grep -q Congratulations
    if test $?
        then echo 'Lab is OK.'
        else echo 'Lab is not OK.'
    fi
    
    echo
    rm -r tmp
}

check_lab_3() {
    mkdir tmp
    wget http://csapp.cs.cmu.edu/3e/target1.tar --directory-prefix tmp --quiet
    tar -xf tmp/target1.tar --directory tmp
    echo Attack Lab
    echo ==========

    # phase 1
    wget https://github.com/zzz0zzz/csapp-3e/raw/master/3-attack-lab/phase-1 --directory-prefix tmp --quiet
    cat tmp/phase-1 | tmp/target1/hex2raw | tmp/target1/ctarget -q | grep -q PASS
    if test $?
      then echo 'Phase 1 is OK.'
      else echo 'Phase 1 is not OK.'
    fi

    # phase 2
    wget https://github.com/zzz0zzz/csapp-3e/raw/master/3-attack-lab/phase-2 --directory-prefix tmp --quiet
    cat tmp/phase-2 | tmp/target1/hex2raw | tmp/target1/ctarget -q | grep -q PASS
    if test $?
      then echo 'Phase 2 is OK.'
      else echo 'Phase 2 is not OK.'
    fi

    # phase 3
    wget https://github.com/zzz0zzz/csapp-3e/raw/master/3-attack-lab/phase-3 --directory-prefix tmp --quiet
    cat tmp/phase-3 | tmp/target1/hex2raw | tmp/target1/ctarget -q | grep -q PASS
    if test $?
      then echo 'Phase 3 is OK.'
      else echo 'Phase 3 is not OK.'
    fi

    # phase 4
    wget https://github.com/zzz0zzz/csapp-3e/raw/master/3-attack-lab/phase-4 --directory-prefix tmp --quiet
    cat tmp/phase-4 | tmp/target1/hex2raw | tmp/target1/rtarget -q | grep -q PASS
    if test $?
      then echo 'Phase 4 is OK.'
      else echo 'Phase 4 is not OK.'
    fi

    # phase 5
    wget https://github.com/zzz0zzz/csapp-3e/raw/master/3-attack-lab/phase-5 --directory-prefix tmp --quiet
    cat tmp/phase-5 | tmp/target1/hex2raw | tmp/target1/rtarget -q | grep -q PASS
    if test $?
      then echo 'Phase 5 is OK.'
      else echo 'Phase 5 is not OK.'
    fi

    rm -r tmp
}

check_all_labs() {
    check_lab_1
    check_lab_2
    check_lab_3
}

check_all_labs
