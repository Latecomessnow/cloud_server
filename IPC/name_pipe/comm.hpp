#pragma once

#ifndef __COMM_H_
#define __COMM_H_

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<unistd.h>
include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

using namespace std;

#define MODE 0666
#define SIZE 128

string ipcPath = "./fifo.ipc";

#endif
