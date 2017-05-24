#pragma once

namespace ParaEngine
{
	class CShapeAABB;
	class CShapeSphere
	{
	public:
		//! Constructor
		inline					CShapeSphere()																		{}
		//! Constructor
		inline					CShapeSphere(const Vector3& center, float radius) : mCenter(center), mRadius(radius)	{}
		//! Constructor
		CShapeSphere(int nb_verts, const Vector3* verts);
		//! Copy constructor
		inline					CShapeSphere(const CShapeSphere& sphere) : mCenter(sphere.mCenter), mRadius(sphere.mRadius)	{}
		//! Destructor
		inline					~CShapeSphere()																		{}

		void	Compute(int nb_verts, const Vector3* verts);
		
		// Access methods
		inline	const Vector3&	GetCenter()						const		{ return mCenter; }
		inline	float			GetRadius()						const		{ return mRadius; }

		inline	const Vector3&	Center()						const		{ return mCenter; }
		inline	float			Radius()						const		{ return mRadius; }

		inline	CShapeSphere&			Set(const Vector3& center, float radius)		{ mCenter = center; mRadius = radius; return *this; }
		inline	CShapeSphere&			SetCenter(const Vector3& center)				{ mCenter = center; return *this; }
		inline	CShapeSphere&			SetRadius(float radius)						{ mRadius = radius; return *this; }

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		*	Tests if a point is contained within the sphere.
		*	\param		p	[in] the point to test
		*	\return		true if inside the sphere
		*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline	bool			Contains(const Vector3& p)		const
		{
			return (mCenter-p).squaredLength() <= mRadius*mRadius;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		*	Tests if a sphere is contained within the sphere.
		*	\param		sphere	[in] the sphere to test
		*	\return		true if inside the sphere
		*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline	bool			Contains(const CShapeSphere& sphere)	const
		{
			// If our radius is the smallest, we can't possibly contain the other sphere
			if(mRadius < sphere.mRadius)	return false;
			// So r is always positive or null now
			float r = mRadius - sphere.mRadius;
			return (mCenter-sphere.mCenter).squaredLength() <= r*r;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		*	Tests if a box is contained within the sphere.
		*	\param		aabb	[in] the box to test
		*	\return		true if inside the sphere
		*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BOOL			Contains(const CShapeAABB& aabb)	const;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		*	Tests if the sphere intersects another sphere
		*	\param		sphere	[in] the other sphere
		*	\return		true if spheres overlap
		*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline	bool			Intersect(const CShapeSphere& sphere)	const
		{
			float r = mRadius + sphere.mRadius;
			return (mCenter-sphere.mCenter).squaredLength() <= r*r;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		*	Checks the sphere is valid.
		*	\return		true if the box is valid
		*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline	BOOL			IsValid()	const
		{
			// Consistency condition for spheres: Radius >= 0.0f
			if(mRadius < 0.0f)	return FALSE;
			return TRUE;
		}
	public:
		Vector3		mCenter;		//!< Sphere center
		float			mRadius;		//!< Sphere radius
	};

}
