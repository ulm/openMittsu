#ifndef OPENMITTSU_DATABASE_CONTACTDATA_H_
#define OPENMITTSU_DATABASE_CONTACTDATA_H_

#include "src/crypto/PublicKey.h"
#include "src/protocol/AccountStatus.h"
#include "src/protocol/ContactIdVerificationStatus.h"
#include "src/protocol/FeatureLevel.h"

#include <QMetaType>
#include <QString>

namespace openmittsu {
	namespace database {
		struct ContactData {
			openmittsu::crypto::PublicKey publicKey;
			QString firstName;
			QString lastName;
			QString nickName;
			QString nickNameRaw;
			openmittsu::protocol::AccountStatus accountStatus;
			openmittsu::protocol::ContactIdVerificationStatus verificationStatus;
			openmittsu::protocol::FeatureLevel featureLevel;
			int color;
			int messageCount;
		};
	}
}

Q_DECLARE_METATYPE(openmittsu::database::ContactData)

#endif // OPENMITTSU_DATABASE_CONTACTDATA_H_
