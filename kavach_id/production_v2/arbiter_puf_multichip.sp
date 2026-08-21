* Arbiter PUF Cell -- Multi-Chip Reliability Test
* 5 virtual chips with decreasing margin, each re-measured 20x with noise.
Vpulse pulse_in 0 PULSE(0 1.8 1n 10p 10p 20n 40n)

R1 pulse_in a 1k
C1 a 0 1p
R2 pulse_in b 1k
C2 b 0 1p

.control
set filetype=ascii

let chip = 1
dowhile chip <= 5

    if chip = 1
        let ra0 = 1050
        let rb0 = 950
    end
    if chip = 2
        let ra0 = 1025
        let rb0 = 975
    end
    if chip = 3
        let ra0 = 1012
        let rb0 = 988
    end
    if chip = 4
        let ra0 = 1005
        let rb0 = 995
    end
    if chip = 5
        let ra0 = 1002
        let rb0 = 998
    end

    alter R1 = $&ra0
    alter R2 = $&rb0
    tran 1p 10n
    meas tran ta0 WHEN v(a)=0.9 RISE=1
    meas tran tb0 WHEN v(b)=0.9 RISE=1
    let true_bit = 0
    if ta0 < tb0
        let true_bit = 1
    end

    let match_count = 0
    let mismatch_count = 0

    let idx = 0
    while idx < 20
        let noise_a = (rnd(21) - 10)
        let noise_b = (rnd(21) - 10)
        let ra_n = ra0 + noise_a
        let rb_n = rb0 + noise_b
        alter R1 = $&ra_n
        alter R2 = $&rb_n

        tran 1p 10n

        meas tran taj WHEN v(a)=0.9 RISE=1
        meas tran tbj WHEN v(b)=0.9 RISE=1

        let this_bit = 0
        if taj < tbj
            let this_bit = 1
        end

        if this_bit = true_bit
            let match_count = match_count + 1
        else
            let mismatch_count = mismatch_count + 1
        end

        let idx = idx + 1
    end

    echo ----------------------------------------
    echo Chip $&chip : Ra0=$&ra0 Rb0=$&rb0 true_bit=$&true_bit
    echo   matches: $&match_count / 20
    echo   mismatches bit flips: $&mismatch_count / 20

    let chip = chip + 1
end
echo ----------------------------------------
echo Multi-chip reliability sweep complete.
.endc

.end
