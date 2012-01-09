#if !defined (__KMS_CORE_H_INSIDE__)
#error "Only <kms-core.h> can be included directly."
#endif

#ifndef __KMS_CONNECTION_H__
#define __KMS_CONNECTION_H__

#include <glib-object.h>
#include "kms-enums.h"
#include "kms-sdp-session.h"

/*
 * Type macros.
 */
#define KMS_TYPE_CONNECTION		(kms_connection_get_type ())
#define KMS_CONNECTION(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), KMS_TYPE_CONNECTION, KmsConnection))
#define KMS_IS_CONNECTION(obj)		(G_TYPE_CHECK_INSTANCE_TYPE ((obj), KMS_TYPE_CONNECTION))
#define KMS_CONNECTION_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), KMS_TYPE_CONNECTION, KmsConnectionClass))
#define KMS_IS_CONNECTION_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), KMS_TYPE_CONNECTION))
#define KMS_CONNECTION_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), KMS_TYPE_CONNECTION, KmsConnectionClass))

typedef struct _KmsConnection		KmsConnection;
typedef struct _KmsConnectionClass	KmsConnectionClass;
typedef struct _KmsConnectionPriv	KmsConnectionPriv;

#define KMS_CONNECTION_ERROR (g_quark_from_string("KmsConnectionError"))

enum {
	KMS_CONNECTION_ERROR_TERMINATED,
	KMS_CONNECTION_ERROR_NOT_IMPLEMENTED,
	KMS_CONNECTION_ERROR_WRONG_ARGUMENT,
};

typedef enum _KmsConnectionType {
	KMS_CONNECTION_TYPE_LOCAL,
	KMS_CONNECTION_TYPE_RTP
} KmsConnectionType ;

/*
typedef enum _KmsConnectionState {
	KMS_CONNECTION_CONNECTED,
	KMS_CONNECTION_DISCONNECTED,
	KMS_CONNECTION_CONNECTING
} KmsConnectionState ;
*/

typedef enum _KmsConnectionMode {
	KMS_CONNECTION_MODE_SENDONLY,	/** Send only */
	KMS_CONNECTION_MODE_RECVONLY,	/** Receive only */
	KMS_CONNECTION_MODE_SENDRECV,	/** Send receive*/
	KMS_CONNECTION_MODE_CONFERENCE,	/** Conference */
	KMS_CONNECTION_MODE_INACTIVE,	/** Inactive */
	KMS_CONNECTION_MODE_LOOPBACK,	/** Loopback */
	KMS_CONNECTION_MODE_CONTTEST,	/** Connection test */
	KMS_CONNECTION_MODE_NETWLOOP,	/** Network loop */
	KMS_CONNECTION_MODE_NETWTEST,	/** Network test */
	KMS_CONNECTION_MODE_EXTENSION	/** Extension mode */
} KmsConnectionMode;

#include "kms-endpoint.h"

struct _KmsConnection {
	GObject parent_instance;

	/* instance members */

	KmsConnectionPriv *priv;
};

struct _KmsConnectionClass {
	GObjectClass parent_class;

	/* class members */

	/* Overridable methods */
	gboolean (*mode_changed)(KmsConnection *self, KmsConnectionMode mode,
					KmsMediaType type, GError **err);
	gboolean (*connect_to_remote)(KmsConnection *self,
					KmsSdpSession *session, GError **err);
	gboolean (*connect)(KmsConnection *self, KmsConnection *other,
					KmsMediaType type, GError **err);
};

/* used by KMS_TYPE_CONNECTION */
GType kms_connection_get_type (void);

/*
 * Method definitions.
 */

/*
 * Minimal required methods
 *
 * get_id
 * get_state
 * get_endpoint
 * set_mode
 * connect_to
 */

/*
 * Moved to a property
gchar *kms_connection_get_id(KmsConnection *self);
*/

/*
KmsConnectionState kms_connection_get_state(KmsConnection *self);
*/

/*
 * Moved to a property
KmsEndpoint *kms_connection_get_endpoint(KmsConnection *self);
*/

gboolean kms_connection_terminate(KmsConnection *self, GError **err);

gboolean kms_connection_set_mode(KmsConnection *self, KmsConnectionMode mode,
								GError **err);

gboolean kms_connection_connect(KmsConnection *self, KmsConnection *other,
						KmsMediaType type, GError **err);

gboolean kms_connection_connect_to_remote(KmsConnection *self,
					KmsSdpSession *session, GError **err);

#endif /* __KMS_CONNECTION_H__ */
