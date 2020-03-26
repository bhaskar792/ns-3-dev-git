/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 NITK Surathkal
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Bhaskar Kataria <bhaskar.k7920@gmail.com>
 */
#ifndef NS_POINTER_TO_CONST_H
#define NS_POINTER_TO_CONST_H

#include "attribute.h"
#include "object.h"

/**
 * \file
 * \ingroup attribute_Pointer
 * ns3::PointerToConstValue attribute value declarations and template implementations.
 */

namespace ns3 {

//  Additional docs for class PointerToConstValue:
/** Hold objects of type Ptr<T>. */
class PointerToConstValue : public AttributeValue
{
public:
  PointerToConstValue ();
  
  /**
   * Construct this PointerToConstValue by referencing an explicit Object.
   *
   * \param [in] object The object to begin with.
   */
  PointerToConstValue (Ptr<Object> object);

  /**
   * Set the value from by reference an Object.
   *
   * \param [in] object The object to reference.
   */
  void SetObject (Ptr<Object> object);

  /**
   * Get the Object referenced by the PointerToConstValue.
   * \returns The Object.
   */
  Ptr<const Object> GetObject (void) const;

  /**
   * Construct this PointerToConstValue by referencing an explicit Object.
   *
   * \tparam T \deduced The type of the object.
   * \param [in] object The object to begin with.
   */
  template <typename T>
  PointerToConstValue (const Ptr<T> & object);

  /**
   * Cast to an Object of type \c T.
   * \tparam T \explicit The type to cast to.
   */ 
  template <typename T>
  operator Ptr<T> () const;

  // Documentation generated by print-introspected-doxygen.cc
  template <typename T>
  void Set (const Ptr<T> & value);

  /** \tparam T \explicit The type to cast to. */
  template <typename T>
  Ptr<T> Get (void) const;

  template <typename T>
  bool GetAccessor ( Ptr< T> &value) const;

  virtual Ptr<AttributeValue> Copy (void) const;
  virtual std::string SerializeToString (Ptr<const AttributeChecker> checker) const;
  virtual bool DeserializeFromString (std::string value, Ptr<const AttributeChecker> checker);

private:
  Ptr<const Object> m_value;
};


class PointerToConstChecker : public AttributeChecker 
{
public:

  /**
   * Get the TypeId of the base type.
   * \returns The base TypeId.
   */
  virtual TypeId GetPointeeTypeId (void) const = 0;
};
  
/**
 * Create a PointerChecker for a type.
 * \tparam T \explicit The underlying type.
 * \returns The PointerChecker.
 */
template <typename T>
Ptr<AttributeChecker> MakePointerToConstChecker (void);

} // namespace ns3



/***************************************************************
 *  Implementation of the templates declared above.
 ***************************************************************/

namespace ns3 {

namespace internal {

/** PointerChecker implementation. */
template <typename T>
class PointerToConstChecker : public ns3::PointerToConstChecker
{
  virtual bool Check (const AttributeValue &val) const {
    const PointerToConstValue *value = dynamic_cast<const PointerToConstValue *> (&val);
    if (value == 0)
      {
        return false;
      }
    if (value->GetObject () == 0)
      {
        return true;
      }
    T *ptr = dynamic_cast<T*> (PeekPointer (value->GetObject ()));
    if (ptr == 0)
      {
        return false;
      }
    return true;
  }
  virtual std::string GetValueTypeName (void) const {
    return "ns3::PointerToConstValue";
  }
  virtual bool HasUnderlyingTypeInformation (void) const {
    return true;
  }
  virtual std::string GetUnderlyingTypeInformation (void) const {
    TypeId tid = T::GetTypeId ();
    return "ns3::Ptr< " + tid.GetName () + " >";
  }
  virtual Ptr<AttributeValue> Create (void) const {
    return ns3::Create<PointerToConstValue> ();
  }
  virtual bool Copy (const AttributeValue &source, AttributeValue &destination) const {
    const PointerToConstValue *src = dynamic_cast<const PointerToConstValue *> (&source);
    PointerToConstValue *dst = dynamic_cast<PointerToConstValue *> (&destination);
    if (src == 0 || dst == 0)
      {
        return false;
      }
    *dst = *src;
    return true;
  }
  virtual TypeId GetPointeeTypeId (void) const {
    return T::GetTypeId ();
  }
};

} // namespace internal

template <typename T>
PointerToConstValue::PointerToConstValue (const Ptr<T> &object)
{
  m_value = object;
}

template <typename T>
void 
PointerToConstValue::Set (const Ptr<T> &object)
{
  m_value = object;
}

template <typename T>
Ptr<T> 
PointerToConstValue::Get (void) const
{
  T *v = dynamic_cast<T *> (PeekPointer (m_value));
  return v;
}

template <typename T>
PointerToConstValue::operator Ptr<T> () const
{
  return Get<T> ();
}

template <typename T>
bool 
PointerToConstValue::GetAccessor ( Ptr<T> &v) const         //v is pointer to const v is effectively constpropagationloss
{ 
  //std::remove_const<T>;
  Ptr< T> ptr = dynamic_cast< T*> (PeekPointer (m_value));
  if (ptr == 0)
    {
      return false;
    }
  v = ptr;
  return true;
}


ATTRIBUTE_ACCESSOR_DEFINE (PointerToConst);

template <typename T>
Ptr<AttributeChecker>
MakePointerToConstChecker (void)
{
  return Create<internal::PointerToConstChecker<T> > ();
}


} // namespace ns3

#endif /* NS_POINTERTOCONST_H */
