// This file defines what appears on the Main Page of the documentation
// generated by doxygen. The file contains no code, and does not appear
// in any cpp include statement.

/**
\mainpage FV3GFS Workflow Manager

\anchor mainpage-top

\section intro Introduction

With the FV3GFS system, a Rocoto driven workflow is being used. This workflow builds on the experiences and work of Kate.Howard and Terry.McGuinness for the GSM, but strips down a lot of complications arising from the use of a cumbersome <b>\c para_config</b>. The <b>\c para_config</b> no longer exists in the workflow and instead a number of <b> \c config </b> files are added, one each for an individual task e.g. <b>\p config.anal</b> contains the analysis specific information. A base config called as <b>\c config.base</b> contains
information related to the machine, super-structure, etc. The idea behind splitting the <b>\p para_config</b> into individual, smaller and managable configs is to provide a means to run any chosen task without the overhead of the full cycling framework. All the configs are located under <b>\c fv3gfs/config</b>

Additionally, the structure of the <b>\c COMROT</b> directory is now modified to look like operations. This enables the use of the workflow much closer to the operational environment, with the exception of the workflow manager.

This is a very much a work in progress and any issues should be reported back and are greatly appreciated.

\section expt_setup Setting up an experiment

To setup an experiment, a python script <b>\c setup_expt.py</b> (located in <b>\c fv3gfs/ush</b>) can be used:

    $> setup_expt.py -h
    usage: setup_expt.py [-h] --pslot PSLOT --configdir CONFIGDIR [--idate IDATE]
                         [--icsdir ICSDIR] [--resdet RESDET] [--resens RESENS]
                         [--comrot COMROT] [--expdir EXPDIR] [--nens NENS]
                         [--cdump CDUMP]

    Setup files and directories to start a GFS parallel. Create EXPDIR, copy
    config files Create COMROT experiment directory structure, link initial
    condition files from $ICSDIR to $COMROT

    optional arguments:
      -h, --help            show this help message and exit
      --pslot PSLOT         parallel experiment name (default: None)
      --configdir CONFIGDIR
                            full path to directory containing the config files
                            (default: None)
      --idate IDATE         date of initial conditions (default: 2016100100)
      --icsdir ICSDIR       full path to initial condition directory (default:
                            /scratch4/NCEPDEV/da/noscrub/Rahul.Mahajan/ICS)
      --resdet RESDET       resolution of the deterministic model forecast
                            (default: 384)
      --resens RESENS       resolution of the ensemble model forecast (default:
                            192)
      --comrot COMROT       full path to COMROT (default: None)
      --expdir EXPDIR       full path to EXPDIR (default: None)
      --nens NENS           number of ensemble members (default: 80)
      --cdump CDUMP         CDUMP to start the experiment (default: gdas)

The above script creates directories <b>\c EXPDIR</b> and <b>\c COMROT</b>. It will make links for initial conditions from a location provided via the <b>\c --icsdir</b> argument for a chosen resolution for the control <b>\c --resdet</b> and the ensemble <b>\c --resens</b>. Experiment name is controlled by the input argument <b>\c --pslot</b>. The script will ask user input in case any of the directories already exist. It will copy experiment configuration files into the <b>\c EXPDIR</b> from <b>\c CONFIGDIR</b>.

Next step is for the user to go through the individual config files (atleast <b>\c config.base</b>) and customize the experiment configuration based on user needs. A stock configuration will be provided at a later stage, but it is imperative that the user understand the steps involved in the system.


\section workflow_setup Setting up the workflow

As described earlier, a \b Rocoto based workflow is being used for cycling a FV3GFS system. The workflow is contained within an \c XML file which will depend on the configuration of your experiment config files. A python script <b>\c setup_workflow.py</b> (located in <b>\c fv3gfs/ush</b>) is provided to setup the XML and will parse information contained within the config files.

    $> setup_workflow.py --help

    Setup XML workflow and CRONTAB for a GFS parallel.

    optional arguments:
      -h, --help       show this help message and exit
      --expdir EXPDIR  full path to experiment directory containing config files
                       (default: current working directory)


This utility creates a workflow XML file \c PSLOT.xml and crontab \c PSLOT.crontab

\b Rocoto uses the XML file <b>\c PSLOT.xml</b> to submit and control the workflow independent of the batch system.

\section rocoto_cheatsheet Rocoto Cheatsheet

For full documentation on \b Rocoto see <a href=http://christopherwharrop.github.io/rocoto>here</a>

To execute the workflow:

    rocotorun -d PSLOT.db -w PSLOT.xml

\b \p PSLOT.db is a SQL database that \b Rocoto uses to keep a track of the workflow state and the user only interacts with it via Rocoto commands. To enable \b Rocoto to monitor the progress of the tasks, <b>\c rocotorun</b> command needs to be repeated frequently and is achieved by setting up a \b cron. \b \p PSLOT.crontab is the crontab created for the machine when <b>\c setup_workflow.py</b> was executed. See \b crontab documentation for setting up a \b cron task and be mindful of its existence after your
xperiment is concluded.

Check the status of the workflow:

    rocotostat -d PSLOT.db -w PSLOT.xml -c all

Check the status of a task in the workflow:

    rocotocheck -d PSLOT.db -w PSLOT.xml -t taskname -c YYYYMMDDHHSS

Kick-off a task of the workflow irrespective of its dependency status:

    rocotoboot -d PSLOT.db -w PSLOT.xml -t taskname -c YYYYMMDDHHSS

Rewind a task in the workflow:

    rocotorewind -d PSLOT.db -w PSLOT.xml -t taskname -c YYYYMMDDHHSS

Terry.McGuinness has an utility \b \p rocoto_viewer.py that takes the \b Rocoto command line interface out of the picture. See GSM documentation for details. It is still helpful to interact with \b Rocoto using native rocoto commands.

*/
