#ifndef OPENMITTSU_CRYPTO_NONCE_H_
#define OPENMITTSU_CRYPTO_NONCE_H_

#include <QByteArray>

#include "src/protocol/ProtocolSpecs.h"

namespace openmittsu {
	namespace crypto {

		class Nonce {
		public:
			Nonce();
			Nonce(QByteArray const& nonceData);
			virtual ~Nonce();

			QByteArray const& getNonce() const;
			unsigned char const* getNonceAsCharPtr() const;

			static constexpr int getNonceLength() {
				return (PROTO_MESSAGE_NONCE_LENGTH_BYTES);
			}
		private:
			QByteArray nonce;
		};

	}
}

#endif // OPENMITTSU_CRYPTO_NONCE_H_
