
This are the project and sources of the Íuvoton NUC1xx flasloader.

The flash loader supports: writing the APROM, Config0 and Config1
register and programming the LDROM.

To program APROM use FlashNUC1xxx.board flashloaders.
To write Config0 and Config1 Registers use "--config" arg with FlashNUC1xxx.board flashloaders.
To program LDROM use LDROMNUC1xxx.board flashloader. Using "--config" with LDROMNUC1xxx.board flashloader
is not allowed.

