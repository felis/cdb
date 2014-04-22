/*****************************************************************************
* Model: cdb_usb.qm
* File:  ./cdb_usb.c
*
* This code has been generated by QM tool (see state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*****************************************************************************/
/*${.::cdb_usb.c} ..........................................................*/
#include "qp_port.h"
#include "cdb_usb.h"
#include "bsp.h"


static QEvt const* l_cliQueueSto[ 10 ];
static QEvt const* l_usbtaskQueueSto[ 10 ];

static QF_MPOOL_EL(PrintStringEvt) l_smallPoolSto[ 10 ];

static QSubscrList    l_subscrSto[MAX_PUB_SIG];


int main(void) {

    CLI_ctor();
    USBTask_ctor();

    QF_init();
    BSP_init();

    QF_poolInit( l_smallPoolSto, sizeof( l_smallPoolSto ), sizeof( l_smallPoolSto[0] ));
    QF_psInit(l_subscrSto, Q_DIM(l_subscrSto));   /* init publish-subscribe */

    QActive_start( AO_CLI, 1, l_cliQueueSto, Q_DIM( l_cliQueueSto ), (void*)0, 0U, (QEvt*)0 );
    QActive_start( AO_USBTask, 2, l_usbtaskQueueSto, Q_DIM( l_usbtaskQueueSto ), (void*)0, 0U, (QEvt*)0 );

    return QF_run();
}