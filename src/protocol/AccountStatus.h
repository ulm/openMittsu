#ifndef OPENMITTSU_PROTOCOL_ACCOUNTSTATUS_H_
#define OPENMITTSU_PROTOCOL_ACCOUNTSTATUS_H_

#include <QMetaType>

namespace openmittsu {
	namespace protocol {

		enum class AccountStatus : int {
			STATUS_UNKNOWN = -1,
			STATUS_INVALID = 2, // Invalid means unregistered or deleted ID
			STATUS_INACTIVE = 1,
			STATUS_ACTIVE = 0,
		};

		class AccountStatusHelper {
		public:
			static AccountStatus fromInt(int contactIdStatus);
			static int toInt(AccountStatus const& contactIdStatus);
		};

	}
}

Q_DECLARE_METATYPE(openmittsu::protocol::AccountStatus)

#endif // OPENMITTSU_PROTOCOL_ACCOUNTSTATUS_H_
