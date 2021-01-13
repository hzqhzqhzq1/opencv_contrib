// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Tencent is pleased to support the open source community by making WeChat QRCode available.
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.

/*
 *  Copyright 2010 ZXing authors All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "zxing/binarybitmap.hpp"

using zxing::BinaryBitmap;
using zxing::BitArray;
using zxing::BitMatrix;
using zxing::ErrorHandler;
using zxing::LuminanceSource;
using zxing::Ref;

// VC++
using zxing::Binarizer;

BinaryBitmap::BinaryBitmap(Ref<Binarizer> binarizer) : binarizer_(binarizer) {}

BinaryBitmap::~BinaryBitmap() {}

Ref<BitArray> BinaryBitmap::getBlackRow(int y, Ref<BitArray> row, ErrorHandler& err_handler) {
    Ref<BitArray> bitary = binarizer_->getBlackRow(y, row, err_handler);
    if (err_handler.ErrCode()) return Ref<BitArray>();
    return bitary;
}

Ref<BitMatrix> BinaryBitmap::getBlackMatrix(ErrorHandler& err_handler) {
    Ref<BitMatrix> bitmtx = binarizer_->getBlackMatrix(err_handler);
    if (err_handler.ErrCode()) return Ref<BitMatrix>();
    return bitmtx;
}

Ref<BitMatrix> BinaryBitmap::getInvertedMatrix(ErrorHandler& err_handler) {
    Ref<BitMatrix> bitmtx = binarizer_->getInvertedMatrix(err_handler);
    if (err_handler.ErrCode()) return Ref<BitMatrix>();
    return bitmtx;
}

int BinaryBitmap::getWidth() const { return binarizer_->getWidth(); }

int BinaryBitmap::getHeight() const { return binarizer_->getHeight(); }

Ref<LuminanceSource> BinaryBitmap::getLuminanceSource() const {
    return binarizer_->getLuminanceSource();
}

bool BinaryBitmap::isCropSupported() const { return getLuminanceSource()->isCropSupported(); }

Ref<BinaryBitmap> BinaryBitmap::crop(int left, int top, int width, int height) {
    return Ref<BinaryBitmap>(new BinaryBitmap(
        binarizer_->createBinarizer(getLuminanceSource()->crop(left, top, width, height))));
}

bool BinaryBitmap::isRotateSupported() const { return binarizer_->isRotateSupported(); }

Ref<BinaryBitmap> BinaryBitmap::rotateCounterClockwise() {
    binarizer_->rotateCounterClockwise();
    return Ref<BinaryBitmap>(new BinaryBitmap(binarizer_));
}