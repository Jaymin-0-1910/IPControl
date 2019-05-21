/* Copyright (c) 2019 Jaymin Suthar. All rights reserved.
 *
 * This file is part of "Input Power Control (IPControl)".
 *
 * IPControl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, only version 3 of the License.
 *
 * IPControl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IPControl.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cerrno>
#include <string>

#include "exception.h"
#include "ipc.h"
#include "module.h"
#include "socket.h"

using namespace std;

static const string SOCKET_PATH = Module::STORAGE + "/.socket";

static socket_server server;
static socket_client* client;

static void initServer() {
	try {
		server.setup(SOCKET_PATH);
	} catch (const socket_error& e) {
		throw(e.what);
	}
}

int IPC::receiveClient() {
	int req = -1;

	try {
		if (server.getfd() < 0) {
			initServer();
		}
		client = server.accept();
		client->recv(&req, sizeof(req));

	} catch (const socket_error& e) {
		switch (errno) {
			case ECONNABORTED:
			case ECONNRESET:
			case EINVAL:
				break;
			default: throw(e.what);
		}
	}
	return req;
}

void IPC::answerClient(int ret) {
	try {
		client->send(&ret, sizeof(ret));

	} catch (const socket_error& e) {
		if (errno != ECONNRESET) {
			throw(e.what);
		}
	}
	delete client;
}

int IPC::requestDaemon(int req) {
	int ret = -1;

	try {
		socket_client client(SOCKET_PATH);
		client.send(&req, sizeof(req));
		client.recv(&ret, sizeof(ret));

	} catch (const socket_error& e) {
		switch (errno) {
			case ECONNREFUSED:
			case ECONNRESET:
			case ENOENT:
				break;
			default: throw(e.what);
		}
	}
	return ret;
}
