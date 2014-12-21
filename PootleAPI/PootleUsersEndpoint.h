#ifndef POOTLE_API_POOTLE_USERS_ENDPOINT_H
#define POOTLE_API_POOTLE_USERS_ENDPOINT_H

#include "PootleEndpoint.h"

#include <ObjectList.h>

#include <map>

class PootleUsersEndpoint;
class PootleTranslationProject;
class PootleUnit;

class PootleUser {
public:
	BString	DateJoined();
	BString	Email();
	BString	FirstName();
	BString	LastName();
	BString	UserName();

	PootleUser() {}

protected:
	friend class PootleUsersEndpoint;
	PootleUser(PootleUsersEndpoint *, BMessage &);
	PootleUser(PootleUsersEndpoint *, int);
	PootleUser(PootleUsersEndpoint *, BString);

private:
	void						_EnsureData();
	PootleUsersEndpoint		*mEndpoint;
	BString						mUri;
	BMessage					mData;
};

class PootleUsersEndpoint : public PootleEndpoint {
public:
	PootleUsersEndpoint(Pootle *pootle)
		: PootleEndpoint(pootle, "users/") {}

	PootleUser					GetByUrl(BString);
	PootleUser					GetById(int id);
protected:
	friend class PootleUser;
		
	PootleUser _get_from_cache(int);
	PootleUser _get_from_cache(BString);

	bool _cache_contains(int);
	bool _cache_contains(BString);
	
	void _add_to_cache(int, PootleUser);
	void _add_to_cache(BString, PootleUser);

private:
	static int _path_to_id(BString);
	std::map<int, PootleUser> mLanguageEndpoints;
};

#endif