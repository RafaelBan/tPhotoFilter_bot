#ifndef SETBASE_H
#define SETBASE_H

#include <ostream>
#include <initializer_list>

#include "rblavltree.h"


namespace rbl
{
    class SetBase
    {
    public:
        explicit
        SetBase();

        virtual void
        clear() = 0;

        virtual bool
        empty() const;

        virtual size_t
        size() const = 0;

        virtual
        ~SetBase();
    };

    template <typename SomeType>
    class Set : public SetBase
    {
        using BaseContainer = AvlTree<SomeType>;

    public:
        using iterator = typename BaseContainer::const_iterator;
        using const_iterator = typename BaseContainer::const_iterator;
        using reverse_iterator = typename BaseContainer::const_reverse_iterator;
        using const_reverse_iterator = typename BaseContainer::const_reverse_iterator;

        Set() = default;

        template <class InputIterator>
        Set(InputIterator first, InputIterator last);

        Set(std::initializer_list<SomeType> initList);

        Set(const Set &s);
        Set(Set &&s);

        virtual
        ~Set();

        Set &
        operator=(const Set &s);
        Set &
        operator=(Set &&s);

        Set &
        operator<<(const SomeType &key);

        Set &
        operator>>(const SomeType &key);
        Set &
        operator>>(const_iterator it);

        Set
        operator+(const Set &s) const;
        Set
        operator*(const Set &s) const;
        Set
        operator-(const Set &s) const;
        Set
        operator^(const Set &s) const;

        Set &
        operator+=(const Set &s);
        Set &
        operator*=(const Set &s);
        Set &
        operator-=(const Set &s);
        Set &
        operator^=(const Set &s);

        bool
        operator==(const Set &s) const;
        bool
        operator!=(const Set &s) const;
        bool
        operator<=(const Set &s) const;
        bool
        operator>=(const Set &s) const;
        bool
        operator>(const Set &s) const;
        bool
        operator<(const Set &s) const;

        Set
        operator+(const SomeType &key) const;
        Set
        operator-(const SomeType &key) const;

        Set &
        operator+=(const SomeType &key);
        Set &
        operator-=(const SomeType &key);

        operator bool();

        template <typename _SomeType>
        friend
        std::ostream &
        operator<<(std::ostream &sout, const Set<_SomeType> &s);

        void
        copy(const Set &s);
        void
        move(Set &s);
        void
        swap(Set &s);

        const_iterator
        find(const SomeType &key) const;

        bool
        insert(const SomeType &key);
        template <class InputIterator>
        void
        insert(InputIterator first, InputIterator last);
        void
        insert(std::initializer_list<SomeType> initList);

        const_iterator
        erase(const SomeType &key);
        const_iterator
        erase(const_iterator it);

        Set
        unite(const Set &s) const;
        Set
        intersect(const Set &s) const;
        Set
        completeRel(const Set &s) const;
        Set
        completeSym(const Set &s) const;

        bool
        equal(const Set &s) const;
        bool
        subOf(const Set &s) const;
        bool
        strictSubOf(const Set &s) const;

        bool
        contains(const SomeType &key) const;

        void
        clear() override;
        size_t
        size()  const override;

        iterator
        begin();
        const_iterator
        begin() const;
        iterator
        end();
        const_iterator
        end() const;

        const_iterator
        cbegin();
        const_iterator
        cbegin() const;
        const_iterator
        cend();
        const_iterator
        cend() const;

        reverse_iterator
        rbegin();
        const_reverse_iterator
        rbegin() const;
        reverse_iterator
        rend();
        const_reverse_iterator
        rend() const;

        const_reverse_iterator
        crbegin();
        const_reverse_iterator
        crbegin() const;
        const_reverse_iterator
        crend();
        const_reverse_iterator
        crend() const;

    protected:

    private:
        BaseContainer storage;
    };
}

#include "rblset.hh"

#endif // SETBASE_H