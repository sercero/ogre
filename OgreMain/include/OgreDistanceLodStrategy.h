/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __Distance_Lod_Strategy_H__
#define __Distance_Lod_Strategy_H__

#include "OgrePrerequisites.h"

#include "OgreLodStrategy.h"
#include "OgreSingleton.h"

namespace Ogre {
    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup LOD
    *  @{
    */

    /** Level of detail strategy based on distance from camera. This is an abstract base class for DistanceLodBoxStrategy and DistanceLodSphereStrategy.

        The purpose of the reference view is to ensure a consistent experience for all users. Monitors of different resolutions and aspect ratios will each have different results for the distance queries.
        @par
            It depends on gameplay testing. If all testers had 16:9 monitors and 110° FOV, then that's the value you should enter (to ensure as much as possible the experience stays consistent for all other users who don't have a 16:9 monitor and/or use a different FOV).
        @par
            If all your testers had 4:3 monitors, then enter a 4:3 resolution.
        @par
            If all your testers had varying resolutions or you just didn't care, then this feature is useless for you and should be disabled (default: disabled).
     */
    class _OgreExport DistanceLodStrategyBase : public LodStrategy
    {
    protected:
        /// @copydoc LodStrategy::getValueImpl
        Real getValueImpl(const MovableObject *movableObject, const Camera *camera) const override;

    public:
        /** Default constructor. */
        DistanceLodStrategyBase(const String& name);

        /// @copydoc LodStrategy::getBaseValue
        Real getBaseValue() const override;

        /// @copydoc LodStrategy::transformBias
        Real transformBias(Real factor) const override;

        /// @copydoc LodStrategy::transformUserValue
        Real transformUserValue(Real userValue) const override;

        /// @copydoc LodStrategy::getIndex
        ushort getIndex(Real value, const Mesh::MeshLodUsageList& meshLodUsageList) const override;

        /// @copydoc LodStrategy::getIndex
        ushort getIndex(Real value, const Material::LodValueList& materialLodValueList) const override;

        /// @copydoc LodStrategy::sort
        void sort(Mesh::MeshLodUsageList& meshLodUsageList) const override;

        /// @copydoc LodStrategy::isSorted
        bool isSorted(const Mesh::LodValueList& values) const override;

        /** Get the squared distance between the camera and the LOD object */
        virtual Real getSquaredDepth(const MovableObject *movableObject, const Ogre::Camera *camera) const = 0;

        /** Sets the reference view upon which the distances were based.
        @note
            This automatically enables use of the reference view.
        @note
            There is no corresponding get method for these values as
            they are not saved, but used to compute a reference value.
        */
        void setReferenceView(Real viewportWidth, Real viewportHeight, Radian fovY);

        /** Enables to disables use of the reference view.
        @note Do not enable use of the reference view before setting it.
        */
        void setReferenceViewEnabled(bool value);

        /** Determine if use of the reference view is enabled */
        bool isReferenceViewEnabled() const;

    private:
        bool mReferenceViewEnabled;
        Real mReferenceViewValue;

    };
    /** @} */
    /** @} */

    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup LOD
    *  @{
    */

    /** Level of detail strategy based on distance from camera to an object's bounding sphere.

        The purpose of the reference view is to ensure a consistent experience for all users. Monitors of different resolutions and aspect ratios will each have different results for the distance queries.
        @par
            It depends on gameplay testing. If all testers had 16:9 monitors and 110° FOV, then that's the value you should enter (to ensure as much as possible the experience stays consistent for all other users who don't have a 16:9 monitor and/or use a different FOV).
        @par
            If all your testers had 4:3 monitors, then enter a 4:3 resolution.
        @par
            If all your testers had varying resolutions or you just didn't care, then this feature is useless for you and should be disabled (default: disabled).
     */
    class _OgreExport DistanceLodSphereStrategy : public DistanceLodStrategyBase, public Singleton<DistanceLodSphereStrategy>
    {
    public:
        /** Default constructor. */
        DistanceLodSphereStrategy();

        Real getSquaredDepth(const MovableObject *movableObject, const Ogre::Camera *camera) const override;

        /// @copydoc Singleton::getSingleton()
        static DistanceLodSphereStrategy& getSingleton(void);
        /// @copydoc Singleton::getSingleton()
        static DistanceLodSphereStrategy* getSingletonPtr(void);
    };
    /** @} */
    /** @} */

    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup LOD
    *  @{
    */

    /** Level of detail strategy based on distance from camera to an object's bounding box.

        The purpose of the reference view is to ensure a consistent experience for all users. Monitors of different resolutions and aspect ratios will each have different results for the distance queries.
        @par
            It depends on gameplay testing. If all testers had 16:9 monitors and 110° FOV, then that's the value you should enter (to ensure as much as possible the experience stays consistent for all other users who don't have a 16:9 monitor and/or use a different FOV).
        @par
            If all your testers had 4:3 monitors, then enter a 4:3 resolution.
        @par
            If all your testers had varying resolutions or you just didn't care, then this feature is useless for you and should be disabled (default: disabled).
     */
    class _OgreExport DistanceLodBoxStrategy : public DistanceLodStrategyBase, public Singleton<DistanceLodBoxStrategy>
    {
    public:
        /** Default constructor. */
        DistanceLodBoxStrategy();

        Real getSquaredDepth(const MovableObject *movableObject, const Ogre::Camera *camera) const override;

        /// @copydoc Singleton::getSingleton()
        static DistanceLodBoxStrategy& getSingleton(void);
        /// @copydoc Singleton::getSingleton()
        static DistanceLodBoxStrategy* getSingletonPtr(void);
    };

    /** @} */
    /** @} */

} // namespace

#endif
