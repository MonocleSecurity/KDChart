/****************************************************************************
**
** This file is part of the KD Chart library.
**
** SPDX-FileCopyrightText: 2001-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDAB-KDChart OR LicenseRef-KDAB-KDChart-US
**
** Licensees holding valid commercial KD Chart licenses may use this file in
** accordance with the KD Chart Commercial License Agreement provided with
** the Software.
**
** Contact info@kdab.com if any conditions of this licensing are not
** clear to you.
**
****************************************************************************/

#ifndef KDCHART_RADAR_COORDINATEPLANE_H
#define KDCHART_RADAR_COORDINATEPLANE_H

#include "KDChartPolarCoordinatePlane.h"

namespace KDChart {

class Chart;

/**
      * @brief Radar coordinate plane
      */
class KDCHART_EXPORT RadarCoordinatePlane : public PolarCoordinatePlane
{
    Q_OBJECT

    Q_DISABLE_COPY(RadarCoordinatePlane)
    KDCHART_DECLARE_PRIVATE_DERIVED_PARENT(RadarCoordinatePlane, Chart *)

public:
    explicit RadarCoordinatePlane(Chart *parent = nullptr);
    ~RadarCoordinatePlane() override;

    /**
         * Set the attributes to be used for axis captions.
         *
         * To disable axis captions, for example, your code should like this:
         * \code
         * TextAttributes ta = plane->textAttributes();
         * ta.setVisible( false );
         * plane-setTextAttributes( ta );
         * \endcode
         */
    void setTextAttributes(const TextAttributes &attr);

    /**
         * \return The attributes used for axis.
         *
         * \note This function always returns a valid set of text attributes:
         * If no special text attributes was set a default one is 
         * returned.
         *
         * \sa setTextAttributes
         */
    const TextAttributes textAttributes() const;
};

}

#endif
