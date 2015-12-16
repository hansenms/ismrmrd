#pragma once
#ifndef ISMRMRD_DATASET_DTYPES_H
#define ISMRMRD_DATASET_DTYPES_H

#include "ismrmrd/ismrmrd.h"

#include <H5Cpp.h>

#ifndef H5_NO_NAMESPACE
    using namespace H5;
#endif // H5_NO_NAMESPACE

namespace ISMRMRD {


template <typename T> struct AcquisitionHeader_with_data
{
    AcquisitionHeader head;
    hvl_t traj;
    hvl_t data;
};

template <typename T> struct ImageHeader_with_data
{
	ImageHeader head;
	hvl_t data;
};

struct IndexEntry
{
    uint32_t stream;
    uint32_t index;
};

template <typename T>
DataType get_hdf5_data_type();

template <> DataType get_hdf5_data_type<char>()
{
	return DataType(PredType::NATIVE_CHAR);
}

template <> DataType get_hdf5_data_type<uint16_t>()
{
	return DataType(PredType::NATIVE_UINT16);
}

template <> DataType get_hdf5_data_type<int16_t>()
{
	return DataType(PredType::NATIVE_INT16);
}

template <> DataType get_hdf5_data_type<uint32_t>()
{
	return DataType(PredType::NATIVE_UINT32);
}

template <> DataType get_hdf5_data_type<int32_t>()
{
	return DataType(PredType::NATIVE_INT32);
}

template <> DataType get_hdf5_data_type<uint64_t>()
{
	return DataType(PredType::NATIVE_UINT64);
}

template <> DataType get_hdf5_data_type<int64_t>()
{
	return DataType(PredType::NATIVE_INT64);
}

template <> DataType get_hdf5_data_type<float>()
{
	return DataType(PredType::NATIVE_FLOAT);
}


template <> DataType get_hdf5_data_type<double>()
{
	return DataType(PredType::NATIVE_DOUBLE);
}

template <> DataType get_hdf5_data_type< std::complex<int16_t> >()
{
    CompType dtype(sizeof(std::complex<int16_t>));
    dtype.insertMember("real", 0, PredType::NATIVE_INT16);
    dtype.insertMember("imag", sizeof(int16_t), PredType::NATIVE_INT16);
	return dtype;
}

template <> DataType get_hdf5_data_type< std::complex<int32_t> >()
{
    CompType dtype(sizeof(std::complex<int32_t>));
    dtype.insertMember("real", 0, PredType::NATIVE_INT32);
    dtype.insertMember("imag", sizeof(int32_t), PredType::NATIVE_INT32);
	return dtype;
}

template <> DataType get_hdf5_data_type< std::complex<float> >()
{
    CompType dtype(sizeof(std::complex<float>));
    dtype.insertMember("real", 0, PredType::NATIVE_FLOAT);
    dtype.insertMember("imag", sizeof(float), PredType::NATIVE_FLOAT);
	return dtype;
}

template <> DataType get_hdf5_data_type< std::complex<double> >()
{
    CompType dtype(sizeof(std::complex<double>));
    dtype.insertMember("real", 0, PredType::NATIVE_DOUBLE);
    dtype.insertMember("imag", sizeof(double), PredType::NATIVE_DOUBLE);
	return dtype;
}

template <> DataType get_hdf5_data_type<IndexEntry>()
{
    CompType dtype(sizeof(IndexEntry));

    dtype.insertMember("stream", HOFFSET(IndexEntry, stream), PredType::NATIVE_UINT32);
    dtype.insertMember("index", HOFFSET(IndexEntry, index), PredType::NATIVE_UINT32);

    return dtype;
}

template <> DataType get_hdf5_data_type<EncodingCounters>()
{
    CompType dtype(sizeof(EncodingCounters));

    dtype.insertMember("kspace_encode_step_0", HOFFSET(EncodingCounters, kspace_encode_step_0), PredType::NATIVE_UINT32);
    dtype.insertMember("kspace_encode_step_1", HOFFSET(EncodingCounters, kspace_encode_step_1), PredType::NATIVE_UINT32);
    dtype.insertMember("kspace_encode_step_2", HOFFSET(EncodingCounters, kspace_encode_step_2), PredType::NATIVE_UINT32);
    dtype.insertMember("average", HOFFSET(EncodingCounters, average), PredType::NATIVE_UINT32);
    dtype.insertMember("slice", HOFFSET(EncodingCounters, slice), PredType::NATIVE_UINT32);
    dtype.insertMember("contrast", HOFFSET(EncodingCounters, contrast), PredType::NATIVE_UINT32);
    dtype.insertMember("phase", HOFFSET(EncodingCounters, phase), PredType::NATIVE_UINT32);
    dtype.insertMember("repetition", HOFFSET(EncodingCounters, repetition), PredType::NATIVE_UINT32);
    dtype.insertMember("set", HOFFSET(EncodingCounters, set), PredType::NATIVE_UINT32);
    dtype.insertMember("segment", HOFFSET(EncodingCounters, segment), PredType::NATIVE_UINT32);

    std::vector<hsize_t> dims(1, ISMRMRD_USER_INTS);
    DataType array_type = ArrayType(PredType::NATIVE_UINT32, 1, &dims[0]);
    dtype.insertMember("user", HOFFSET(EncodingCounters, user), array_type);

    return dtype;
}

template <> DataType get_hdf5_data_type<AcquisitionHeader>()
{
    CompType dtype(sizeof(AcquisitionHeader));

    dtype.insertMember("signature", HOFFSET(AcquisitionHeader, signature),  PredType::NATIVE_UINT32);
    dtype.insertMember("entity_type", HOFFSET(AcquisitionHeader, entity_type),  PredType::NATIVE_UINT32);
    dtype.insertMember("storage_type", HOFFSET(AcquisitionHeader, storage_type),  PredType::NATIVE_UINT32);
    dtype.insertMember("stream", HOFFSET(AcquisitionHeader, stream),  PredType::NATIVE_UINT32);
    dtype.insertMember("time_stamp", HOFFSET(AcquisitionHeader, time_stamp),  PredType::NATIVE_UINT64);
    dtype.insertMember("flags",  HOFFSET(AcquisitionHeader, flags),  PredType::NATIVE_UINT64);
    dtype.insertMember("scan_counter",  HOFFSET(AcquisitionHeader, scan_counter),  PredType::NATIVE_UINT32);

    std::vector<hsize_t> dims(1, ISMRMRD_PHYS_STAMPS);
    DataType array_type = ArrayType(PredType::NATIVE_UINT32, 1, &dims[0]);
    dtype.insertMember("physiology_time_stamp", HOFFSET(AcquisitionHeader, physiology_time_stamp), array_type);
    dtype.insertMember("number_of_samples",  HOFFSET(AcquisitionHeader, number_of_samples),  PredType::NATIVE_UINT32);
    dtype.insertMember("available_channels",  HOFFSET(AcquisitionHeader, available_channels),  PredType::NATIVE_UINT32);
    dtype.insertMember("active_channels",  HOFFSET(AcquisitionHeader, active_channels),  PredType::NATIVE_UINT32);

    dims[0] = ISMRMRD_CHANNEL_MASKS;
    DataType mask_array_type = ArrayType(PredType::NATIVE_UINT64, 1, &dims[0]);
    dtype.insertMember("channel_mask",  HOFFSET(AcquisitionHeader, channel_mask), mask_array_type);
    dtype.insertMember("discard_pre",  HOFFSET(AcquisitionHeader, discard_pre),  PredType::NATIVE_UINT32);
    dtype.insertMember("discard_post",  HOFFSET(AcquisitionHeader, discard_post),  PredType::NATIVE_UINT32);
    dtype.insertMember("center_sample",  HOFFSET(AcquisitionHeader, center_sample),  PredType::NATIVE_UINT32);
    dtype.insertMember("encoding_space_ref",  HOFFSET(AcquisitionHeader, encoding_space_ref),  PredType::NATIVE_UINT32);
    dtype.insertMember("trajectory_dimensions", HOFFSET(AcquisitionHeader, trajectory_dimensions),  PredType::NATIVE_UINT32);
    dtype.insertMember("dwell_time_ns",  HOFFSET(AcquisitionHeader, dwell_time_ns),  PredType::NATIVE_UINT32);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType position_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("position",  HOFFSET(AcquisitionHeader, position), position_array_type);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType read_dir_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("read_dir",  HOFFSET(AcquisitionHeader, read_dir), read_dir_array_type);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType phase_dir_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("phase_dir",  HOFFSET(AcquisitionHeader, phase_dir), phase_dir_array_type);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType slice_dir_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("slice_dir",  HOFFSET(AcquisitionHeader, slice_dir), slice_dir_array_type);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType table_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("patient_table_position",  HOFFSET(AcquisitionHeader, patient_table_position), table_array_type);

    DataType ec_type = get_hdf5_data_type<EncodingCounters>();
    dtype.insertMember("idx",  HOFFSET(AcquisitionHeader, idx), ec_type);

    dims[0] = ISMRMRD_USER_INTS;
    DataType user_int_array_type = ArrayType(PredType::NATIVE_INT32, 1, &dims[0]);
    dtype.insertMember("user_int",  HOFFSET(AcquisitionHeader, user_int), user_int_array_type);

    dims[0] = ISMRMRD_USER_FLOATS;
    DataType user_float_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("user_float",  HOFFSET(AcquisitionHeader, user_float), user_float_array_type);

    return dtype;
}

template <typename T> DataType get_hdf5_acquisition_data_type()
{
    CompType dtype(sizeof(AcquisitionHeader_with_data<T>));

    DataType head_type = get_hdf5_data_type<AcquisitionHeader>();
    DataType traj_type = DataType(H5Tvlen_create(get_hdf5_data_type<float>().getId()));
    DataType cplx_type = DataType(H5Tvlen_create(get_hdf5_data_type< std::complex<T> >().getId()));

    dtype.insertMember("head", HOFFSET(AcquisitionHeader_with_data<T>, head), head_type);
    dtype.insertMember("traj", HOFFSET(AcquisitionHeader_with_data<T>, traj), traj_type);
    dtype.insertMember("data", HOFFSET(AcquisitionHeader_with_data<T>, data), cplx_type);

    return dtype;
}

template <> DataType get_hdf5_data_type<AcquisitionHeader_with_data<float> >()
{
	return get_hdf5_acquisition_data_type<float>();
}

template <> DataType get_hdf5_data_type<AcquisitionHeader_with_data<int16_t> >()
{
	return get_hdf5_acquisition_data_type<int16_t>();
}

template <> DataType get_hdf5_data_type<AcquisitionHeader_with_data<int32_t> >()
{
	return get_hdf5_acquisition_data_type<int32_t>();
}

template <> DataType get_hdf5_data_type<ImageHeader>()
{
    CompType dtype(sizeof(ImageHeader));

    dtype.insertMember("signature", HOFFSET(ImageHeader, signature),  PredType::NATIVE_UINT32);
    dtype.insertMember("entity_type", HOFFSET(ImageHeader, entity_type),  PredType::NATIVE_UINT32);
    dtype.insertMember("storage_type", HOFFSET(ImageHeader, storage_type),  PredType::NATIVE_UINT32);
    dtype.insertMember("stream", HOFFSET(ImageHeader, stream),  PredType::NATIVE_UINT32);
    dtype.insertMember("time_stamp", HOFFSET(ImageHeader, time_stamp),  PredType::NATIVE_UINT64);
    dtype.insertMember("flags",  HOFFSET(ImageHeader, flags),  PredType::NATIVE_UINT64);

    std::vector<hsize_t> dims(1, 3);
    DataType matrix_array_type = ArrayType(PredType::NATIVE_UINT32, 1, &dims[0]);
    dtype.insertMember("matrix_size", HOFFSET(ImageHeader, matrix_size), matrix_array_type);
    DataType fov_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("field_of_view", HOFFSET(ImageHeader, field_of_view), matrix_array_type);
    dtype.insertMember("channels",  HOFFSET(ImageHeader, channels),  PredType::NATIVE_UINT32);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType position_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("position",  HOFFSET(ImageHeader, position), position_array_type);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType read_dir_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("read_dir",  HOFFSET(ImageHeader, read_dir), read_dir_array_type);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType phase_dir_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("phase_dir",  HOFFSET(ImageHeader, phase_dir), phase_dir_array_type);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType slice_dir_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("slice_dir",  HOFFSET(ImageHeader, slice_dir), slice_dir_array_type);

    dims[0] = ISMRMRD_POSITION_LENGTH;
    DataType table_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("patient_table_position",  HOFFSET(ImageHeader, patient_table_position), table_array_type);

    dtype.insertMember("average",  HOFFSET(ImageHeader, average),  PredType::NATIVE_UINT32);
    dtype.insertMember("slice",  HOFFSET(ImageHeader, slice),  PredType::NATIVE_UINT32);
    dtype.insertMember("phase",  HOFFSET(ImageHeader, phase),  PredType::NATIVE_UINT32);
    dtype.insertMember("repetition",  HOFFSET(ImageHeader, repetition),  PredType::NATIVE_UINT32);
    dtype.insertMember("set",  HOFFSET(ImageHeader, set),  PredType::NATIVE_UINT32);

    dims[0] = ISMRMRD_PHYS_STAMPS;
    DataType array_type = ArrayType(PredType::NATIVE_UINT32, 1, &dims[0]);
    dtype.insertMember("physiology_time_stamp", HOFFSET(ImageHeader, physiology_time_stamp), array_type);

    dtype.insertMember("image_type",  HOFFSET(ImageHeader, image_type),  PredType::NATIVE_UINT32);
    dtype.insertMember("image_index",  HOFFSET(ImageHeader, image_index),  PredType::NATIVE_UINT32);
    dtype.insertMember("image_series_index",  HOFFSET(ImageHeader, image_series_index),  PredType::NATIVE_UINT32);

    dims[0] = ISMRMRD_USER_INTS;
    DataType user_int_array_type = ArrayType(PredType::NATIVE_INT32, 1, &dims[0]);
    dtype.insertMember("user_int",  HOFFSET(ImageHeader, user_int), user_int_array_type);

    dims[0] = ISMRMRD_USER_FLOATS;
    DataType user_float_array_type = ArrayType(PredType::NATIVE_FLOAT, 1, &dims[0]);
    dtype.insertMember("user_float",  HOFFSET(ImageHeader, user_float), user_float_array_type);

    dtype.insertMember("attribute_string_len",  HOFFSET(ImageHeader, attribute_string_len),  PredType::NATIVE_UINT32);

    return dtype;
}

template <typename T> DataType get_hdf5_image_data_type()
{
    CompType dtype(sizeof(ImageHeader_with_data<T>));

    DataType head_type = get_hdf5_data_type<ImageHeader>();
    DataType data_type = DataType(H5Tvlen_create(get_hdf5_data_type<T>().getId()));

    dtype.insertMember("head", HOFFSET(ImageHeader_with_data<T>, head), head_type);
    dtype.insertMember("data", HOFFSET(ImageHeader_with_data<T>, data), data_type);

    return dtype;
}

template <> DataType get_hdf5_data_type<ImageHeader_with_data<uint16_t> >()
{
	return get_hdf5_image_data_type<uint16_t>();
}

template <> DataType get_hdf5_data_type<ImageHeader_with_data<int16_t> >()
{
	return get_hdf5_image_data_type<uint16_t>();
}

template <> DataType get_hdf5_data_type<ImageHeader_with_data<uint32_t> >()
{
	return get_hdf5_image_data_type<uint32_t>();
}

template <> DataType get_hdf5_data_type<ImageHeader_with_data<int32_t> >()
{
	return get_hdf5_image_data_type<int32_t>();
}

template <> DataType get_hdf5_data_type<ImageHeader_with_data<float> >()
{
	return get_hdf5_image_data_type<float>();
}

template <> DataType get_hdf5_data_type<ImageHeader_with_data<double> >()
{
	return get_hdf5_image_data_type<double>();
}

template <> DataType get_hdf5_data_type<ImageHeader_with_data< std::complex<float> > >()
{
	return get_hdf5_image_data_type<std::complex<float> >();
}

template <> DataType get_hdf5_data_type<ImageHeader_with_data< std::complex<double> > >()
{
	return get_hdf5_image_data_type<std::complex<double> >();
}

} // namespace ISMRMRD

#endif // ISMRMRD_DATASET_DTYPES_H
