#include <fstream>
#include <iomanip>
#include <iostream>
#include <eigen3/Eigen/Eigen>

Eigen::Matrix3d transformMatrixSecToPrim(double q, double l)
{
    Eigen::Matrix3d T;

    T << std::cos(q), -std::sin(q), l * std::cos(q),
        std::sin(q), std::cos(q), l * std::sin(q),
        0, 0, 1;

    return T;
}

struct CoordinateSytem
{
    Eigen::Matrix3d ToGlobal;
    Eigen::Matrix3d ToLocal;
};

class LinkJoint
{
public:
    LinkJoint(double initialAngle, double linkLength, Eigen::Matrix3d ToGlobalTransform) : angle{initialAngle}, linkLength{linkLength}
    {
        coordSys.ToGlobal = ToGlobalTransform;
        coordSys.ToLocal = coordSys.ToGlobal.inverse();
    };

    Eigen::Matrix3d getNextCoordSysTransformMatrix()
    {
        return coordSys.ToGlobal * transformMatrixSecToPrim(angle, linkLength);
    }

    void setAngle(double newAngle)
    {
        angle = newAngle;
        NextCoordSystemToGlobal = transformMatrixSecToPrim(angle, linkLength);
    }

    double getAngle()
    {
        return angle;
    }

    double getLinkLength()
    {
        return linkLength;
    }

    Eigen::Matrix3d getLocalToGlobalTransform()
    {
        return coordSys.ToGlobal;
    }

    Eigen::Matrix3d getGlobalToLocalTransform()
    {
        return coordSys.ToLocal;
    }

    void updateGlobalTransform(Eigen::Matrix3d T)
    {
        coordSys.ToGlobal = T;
        coordSys.ToLocal = T.inverse();
    }

private:
    CoordinateSytem coordSys;
    Eigen::Matrix3d NextCoordSystemToGlobal;
    double linkLength;
    double angle;
};

class FourJointRobotArm
{
public:
    FourJointRobotArm(double q1, double l1, double q2, double l2, double q3, double l3)
        : baseJoint(q1, l1, Eigen::Matrix3d::Identity()),
          shoulderJoint(q2, l2, baseJoint.getNextCoordSysTransformMatrix()),
          elbowJoint(q3, l3, shoulderJoint.getNextCoordSysTransformMatrix()),
          wristJoint(0, 0, elbowJoint.getNextCoordSysTransformMatrix()),
          l1(l1),
          l2(l2),
          l3(l3)
    {
    }

    void setBaseAngle(double q)
    {
        baseJoint.setAngle(q);
        shoulderJoint.updateGlobalTransform(baseJoint.getNextCoordSysTransformMatrix());
    }

    void setShoulderAngle(double q)
    {
        shoulderJoint.setAngle(q);
        elbowJoint.updateGlobalTransform(shoulderJoint.getNextCoordSysTransformMatrix());
    }

    void setElbowAngle(double q)
    {
        elbowJoint.setAngle(q);
        wristJoint.updateGlobalTransform(elbowJoint.getNextCoordSysTransformMatrix());
    }

    void setJointAngles(double q1, double q2, double q3)
    {
        setBaseAngle(q1);
        setShoulderAngle(q2);
        setElbowAngle(q3);
    }

    Eigen::Matrix3d getBaseToGlobalTransform()
    {
        return baseJoint.getLocalToGlobalTransform();
    }

    Eigen::Matrix3d getShoulderToGlobalTransform()
    {
        return shoulderJoint.getLocalToGlobalTransform();
    }

    Eigen::Matrix3d getElbowToGlobalTransform()
    {
        return elbowJoint.getLocalToGlobalTransform();
    }

    Eigen::Matrix3d getEndEffectorToGlobalTransform()
    {
        return wristJoint.getLocalToGlobalTransform();
    }

    Eigen::Vector3d getBasePosition()
    {
        return getJointPosition(baseJoint);
    }

    Eigen::Vector3d getShoulderPosition()
    {
        return getJointPosition(shoulderJoint);
    }

    Eigen::Vector3d getElbowPosition()
    {
        return getJointPosition(elbowJoint);
    }

    Eigen::Vector3d getEndEffectorPosition()
    {
        return getJointPosition(wristJoint);
    }

    double getBaseAngle()
    {
        return baseJoint.getAngle();
    }

    double getShoulderAngle()
    {
        return shoulderJoint.getAngle();
    }

    double getElbowAngle()
    {
        return elbowJoint.getAngle();
    }

    double getBaseLinkLength()
    {
        return baseJoint.getLinkLength();
    }

    double getShoulderLinkLength()
    {
        return shoulderJoint.getLinkLength();
    }

    double getElbowLinkLength()
    {
        return elbowJoint.getLinkLength();
    }

private:
    LinkJoint baseJoint;
    LinkJoint shoulderJoint;
    LinkJoint elbowJoint;
    LinkJoint wristJoint;
    double l1;
    double l2;
    double l3;

    Eigen::Vector3d getJointPosition(LinkJoint joint)
    {
        Eigen::Matrix3d T = joint.getLocalToGlobalTransform();
        return T * Eigen::Vector3d(0, 0, 1);
    }
};

Eigen::Matrix3d endEffectorTransform(double q, double l)
{
    Eigen::Matrix3d T;

    T << std::cos(q), -std::sin(q), l * std::cos(q),
        std::sin(q), std::cos(q), l * std::sin(q),
        0, 0, 1;

    return T;
}

int main(int argc, char *argv[])
{
    // by defult, use the file joint_angles.txt, but if you supply a command line argument, use that instead
    std::string input_filename{"joint_angles.txt"};
    if (argc >= 2)
    {
        input_filename = argv[1];
    }
    std::ifstream ifs(input_filename);

    if (!ifs.good())
    {
        std::cerr << "Failed to open file " << input_filename << std::endl;
        return 0;
    }

    double l1{1.0};
    double l2{0.5};
    double l3{0.25};

    while (ifs.peek() != -1)
    {
        double q1, q2, q3;
        ifs >> q1 >> q2 >> q3;

        FourJointRobotArm robot(0, l1, 0, l2, 0, l3);
        robot.setJointAngles(q1, q2, q3);

        Eigen::Vector3d p = robot.getEndEffectorPosition();

        std::cout << std::setprecision(3) << p.x() << "\n"
                  << p.y() << std::endl;
    }
}