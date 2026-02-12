.section .time_critical.firmware
.global firmware
.type firmware, %object
.balign 4
firmware:
.incbin "ProtocolConverter/src/SoftSP-Grappler_S6.bin"
