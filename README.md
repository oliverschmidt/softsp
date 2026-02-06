# softSP

This project is based on [A2Pico](https://github.com/oliverschmidt/a2pico).

With this firmware, the A2Pico emulates a DIY [softSP](https://web.archive.org/web/20241127055635/http://www.mfa2lab.com/opcart/index.php?route=product/product&product_id=56) card that allows to use SmartPort devices connected to a **Disk II controller card in slot 6**.

The [DIYSP V6 firmware](https://web.archive.org/web/20250118171322/http://www.mfa2lab.com/softsp-v6-release/) is used for A2Pico with kind permission of Wing Yeung, MFA2 WorkShop.

That firmware is intended for a [Grappler+ Printer Interface](https://mirrors.apple2.org.za/Apple%20II%20Documentation%20Project/Interface%20Cards/Parallel/Orange%20Micro%20Grappler%20plus%20Printer%20Interface/).
This project therefore emulates the ROM of that very interface.

However, this project goes beyond the capabilities of both commercially manufactured and DIY softSP cards in one key aspect: It enables autostart from the softSP card in an Apple ][+ and an unenhanced Apple //e. These machines do not normally autostart from the softSP card (or any SmartPort card).

Therefore, it is recommended on all machines to install the **A2Pico in slot 7** to enable autostart from this instead of the Disk II controller card.
