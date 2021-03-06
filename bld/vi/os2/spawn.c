/****************************************************************************
*
*                            Open Watcom Project
*
* Copyright (c) 2015-2019 The Open Watcom Contributors. All Rights Reserved.
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  Spawn external commands.
*
****************************************************************************/


#include "vi.h"
#define INCL_DOSPROCESS
#define INCL_DOSERRORS
#include <os2.h>
#include "fcbmem.h"


void ResetSpawnScreen( void )
{
}

long MySpawn( const char *cmd )
{
    USHORT              rc;
    RESULTCODES         returncodes;
    char                path[_MAX_PATH];
    char                all[_MAX_PATH + 128];
    cmd_struct          cmds;

    GetSpawnCommandLine( path, cmd, &cmds );
    cmds.cmd[cmds.len] = '\0';
    strcpy( all, path );
    strcat( all, " " );
    strcat( all, cmds.cmd );

    rc = DosExecPgm( NULL, 0, EXEC_SYNC, all, NULL, &returncodes, path );
    if( rc != 0 ) {
        return( -1L );
    }
    return( returncodes.codeResult );
}
