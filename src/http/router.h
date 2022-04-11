// Copyright 2022 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_HTTP_ROUTER_H
#define FS_HTTP_ROUTER_H

#include "responder.h"
#include "../luascript.h"

namespace Http
{

/** \brief Represents the lua HTTP API subsystem
 * This class is responsible for loading and maintaining the
 * lua HTTP API subsystem. When an API event occurs it dispatches
 * the appropriate lua callback.
 * \remark Thread-unsafe - objects of this class should only be manipulated
 * from within the dispatcher thread's context.
 */
class Router final
{
	/// Represents the lua interface handle used by the HTTP API subsystem
	LuaScriptInterface interface{"HTTP API Router interface"};
	/// Represents the handle to the request handling lua callback
	int32_t luaRequestHandlerId = -1;
	/// Represents the handle to the session creation lua callback
	int32_t luaSessionOpenId = -1;
	/// Represents the handle to the session destruction lua callback
	int32_t luaSessionCloseId = -1;

	void sendInternalServerError(Responder& responder) const;
public:
	Router();

	/** \brief Loads the lua HTTP callbacks
	 *
	 * Attempts to load the lua routing callbacks. In the event of failure
	 * it returns false and the API is disabled(HTTP 500 Internal Server Error is sent).
	 */
	bool loadRoutingFunctions();

	/** \brief Handles an incoming HTTP request
	 *
	 * Attempts to call the lua HTTP API subsystem's callback function to handle the
	 * incoming request. If the callback has not been loaded properly or cannot
	 * be called then a HTTP 500 Internal Server Error is sent as a response.
	 * \param[in] responder - the object that contains the request data and a handle
	 * to send a response
	 * \param[in] peerId - unique ID of a remote \ref Peer, used by lua to identify which
	 * connection this request belongs to
	 */
	void handleRequest(Responder responder, PeerId peerId);

	/** \brief Handles the opening of an HTTP connection and session
	 *
	 * Attempts to dispatch the lua session open handler which allows the API side
	 * to track open sessions. In the event of failure(e.g. when the handler is not present)
	 * no action is taken.
	 * \param[in] peerId - unique ID of a remote \ref Peer, used by lua to identify which
	 * connection this event belongs to
	 */
	void handleSessionOpen(PeerId peerId);

	/** \brief Handles the closing of an HTTP connection and session
	 *
	 * Attempts to dispatch the lua session close handler which allows the API side
	 * to track session close events and release any resources that are no longer
	 * needed.
	 * \param[in] peerId - unique ID of a remote \ref Peer, used by lua to identify which
	 * connection this event belongs to
	 */
	void handleSessionClose(PeerId peerId);
};

} //namespace Http

#endif //FS_HTTP_ROUTER_H
