#include "ismrmrd/ismrmrd.h"
#include "ismrmrd/version.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

using namespace ISMRMRD;

typedef boost::mpl::list<int16_t,int32_t, float> test_types;

BOOST_AUTO_TEST_SUITE(Acquisitions)

static void check_header(const AcquisitionHeader& chead);

BOOST_AUTO_TEST_CASE_TEMPLATE(acquisition_create, T, test_types)
{
    Acquisition<T> acq;
    AcquisitionHeader head = acq.getHead();

    // Check that header is of expected size
    size_t expected_size = 4 * sizeof(uint32_t) +
            (10 + ISMRMRD_PHYS_STAMPS) * sizeof(uint32_t) +
            ISMRMRD_USER_INTS * sizeof(int32_t) +
            (2 + ISMRMRD_CHANNEL_MASKS) * sizeof(uint64_t) +
            ((2 * ISMRMRD_POSITION_LENGTH) + (3 * ISMRMRD_DIRECTION_LENGTH) +
                    1 + ISMRMRD_USER_FLOATS) * sizeof(float) +
            (9 + ISMRMRD_USER_INTS) * sizeof(uint32_t);

    BOOST_CHECK_EQUAL(sizeof(head), expected_size);

    // Check that header is initialized properly
    check_header(head);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(acquisition_copy, T, test_types)
{
    Acquisition<T> acq1;
    check_header(acq1.getHead());
    Acquisition<T> acq2(acq1);
    check_header(acq2.getHead());

    BOOST_CHECK(acq1.getHead() == acq2.getHead());
}


BOOST_AUTO_TEST_CASE_TEMPLATE(acquisition_getters_setters, T, test_types)
{
    Acquisition<T> acq;

    // TODO: implement
}

BOOST_AUTO_TEST_CASE_TEMPLATE(acquisition_resize, T, test_types)
{
    Acquisition<T> acq;
    check_header(acq.getHead());
    BOOST_CHECK_EQUAL(acq.getData().size(), 0);

    acq.resize(72, 32);
    BOOST_CHECK_EQUAL(acq.getNumberOfSamples(), 72);
    BOOST_CHECK_EQUAL(acq.getActiveChannels(), 32);
    BOOST_CHECK_EQUAL(acq.getData().size(), 72*32);

    std::vector<T> zeros(72*32, 0);
    BOOST_CHECK_EQUAL_COLLECTIONS(zeros.begin(), zeros.end(),
            acq.getData().begin(), acq.getData().end());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(acquisition_serialize, T, test_types)
{
    Acquisition<T> acq;
    acq.resize(144,32);
    acq.setTrajectoryDimensions(3);

    std::vector<unsigned char> buffer = acq.serialize();

    Acquisition<T> acq2;
    acq2.deserialize(buffer);
    BOOST_CHECK_EQUAL_COLLECTIONS(acq.getData().begin(), acq.getData().end(),
                                  acq2.getData().begin(), acq2.getData().end());
    
    BOOST_CHECK_EQUAL_COLLECTIONS(acq.getTraj().begin(), acq.getTraj().end(),
                                  acq2.getTraj().begin(), acq2.getTraj().end());
    
    BOOST_CHECK(acq.getHead() == acq2.getHead());
}

static void check_header(const AcquisitionHeader& chead)
{
    BOOST_CHECK_EQUAL(chead.signature, ISMRMRD_SIGNATURE);
    BOOST_CHECK_EQUAL(chead.number_of_samples, 0);
    BOOST_CHECK_EQUAL(chead.available_channels, 1);
    BOOST_CHECK_EQUAL(chead.active_channels, 1);
    BOOST_CHECK_EQUAL(chead.flags, 0);
    BOOST_CHECK_EQUAL(chead.scan_counter, 0);
    for (int idx = 0; idx < ISMRMRD_PHYS_STAMPS; idx++) {
        BOOST_CHECK_EQUAL(chead.physiology_time_stamp[idx], 0);
    }

    for (int idx = 0; idx < ISMRMRD_CHANNEL_MASKS; idx++) {
        BOOST_CHECK_EQUAL(chead.channel_mask[idx], 0);
    }
    BOOST_CHECK_EQUAL(chead.discard_pre, 0);
    BOOST_CHECK_EQUAL(chead.discard_post, 0);
    BOOST_CHECK_EQUAL(chead.center_sample, 0);
    BOOST_CHECK_EQUAL(chead.encoding_space_ref, 0);
    BOOST_CHECK_EQUAL(chead.trajectory_dimensions, 0);
    BOOST_CHECK_EQUAL(chead.dwell_time_ns, 0);
    for (int idx = 0; idx < ISMRMRD_POSITION_LENGTH; idx++) {
        BOOST_CHECK_EQUAL(chead.position[idx], 0);
    }
    for (int idx = 0; idx < ISMRMRD_DIRECTION_LENGTH; idx++) {
        BOOST_CHECK_EQUAL(chead.read_dir[idx], 0);
    }
    for (int idx = 0; idx < ISMRMRD_DIRECTION_LENGTH; idx++) {
        BOOST_CHECK_EQUAL(chead.phase_dir[idx], 0);
    }
    for (int idx = 0; idx < ISMRMRD_DIRECTION_LENGTH; idx++) {
        BOOST_CHECK_EQUAL(chead.slice_dir[idx], 0);
    }
    for (int idx = 0; idx < ISMRMRD_POSITION_LENGTH; idx++) {
        BOOST_CHECK_EQUAL(chead.patient_table_position[idx], 0);
    }

    // EncodingCounters
    BOOST_CHECK_EQUAL(chead.idx.kspace_encode_step_1, 0);
    BOOST_CHECK_EQUAL(chead.idx.kspace_encode_step_2, 0);
    BOOST_CHECK_EQUAL(chead.idx.average, 0);
    BOOST_CHECK_EQUAL(chead.idx.slice, 0);
    BOOST_CHECK_EQUAL(chead.idx.contrast, 0);
    BOOST_CHECK_EQUAL(chead.idx.phase, 0);
    BOOST_CHECK_EQUAL(chead.idx.repetition, 0);
    BOOST_CHECK_EQUAL(chead.idx.set, 0);
    BOOST_CHECK_EQUAL(chead.idx.segment, 0);

    for (int idx = 0; idx < ISMRMRD_USER_INTS; idx++) {
        BOOST_CHECK_EQUAL(chead.idx.user[idx], 0);
    }

    for (int idx = 0; idx < ISMRMRD_USER_INTS; idx++) {
        BOOST_CHECK_EQUAL(chead.user_int[idx], 0);
    }
    for (int idx = 0; idx < ISMRMRD_USER_FLOATS; idx++) {
        BOOST_CHECK_EQUAL(chead.user_float[idx], 0);
    }
}

BOOST_AUTO_TEST_SUITE_END()
