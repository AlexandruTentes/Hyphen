#pragma once

#define INTERFACE_H_

class Interface
{
	public:
		virtual Interface * clone() const = 0;
};

template <class Derived>
class Interfaced : public Interface
{
	public:
		virtual Interface * clone() const
		{
			return new Derived(static_cast<Derived const &>(*this));
		}
};