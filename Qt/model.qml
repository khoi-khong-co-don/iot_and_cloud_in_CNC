import QtQuick 2.2 as QQ2
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.15


Entity {
    property real distanX: -3.0
    property real distanY: -4.0
    property real distanZ: 7.5

    property real userDistanX1: 0.7
    property real userDistanY1: 0.65
    property bool t: false

    id: sceneRoot
    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0, 8, 25)
//        position: Qt.vector3d( 0, 0, -40)
        upVector: Qt.vector3d( 0.0, 0.0, 0.0 )
        viewCenter: Qt.vector3d( 0, 0, 0 )
    }

    OrbitCameraController {
        camera: camera
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                clearColor: Qt.rgba(1,1,0.8 , 1)           //0, 0.5, 1, 1
                camera: camera
                showDebugOverlay: true
            }
        },
        // Event Source will be set by the Qt3DQuickWindow
        InputSettings { }
    ]

        ///////////////// máy cnc///////////////////////////////////
    SceneLoader{
        id: sceneLoader
        source: "qrc:/obj/assem1.obj"
    }

    Transform{
        id: sceneLoaderTransform
        translation: Qt.vector3d(0,-3,5)
        scale: 0.01
//            translation: Qt.vector3d(-50,-80,100)
//            scale: 0.05
    }
    PhongMaterial {
        id: material1
    //    ambient: "gray"
//        diffuse: "blue"
//        specular: "blue"
//        shininess: 50.0
    }

    // truc x
    SceneLoader{
        id: sceneLoader2
        source: "qrc:/obj/assem2.obj"
    }
    Transform{
        id: sceneLoaderTransform2
        property real userDistanX
//        translation: Qt.vector3d(-4.5,-0.4,-1)      // Z: -3.5 -> 2
//        scale: 0.01
//        rotationY:  180
        matrix: {
            var m3 = Qt.matrix4x4();
            m3.translate(Qt.vector3d(0.2,-0.4,userDistanX));
            m3.scale(0.01, 0.01, 0.01)
            return m3;
        }
    }
    PhongMaterial {
        id: material2
        ambient: "red"
        diffuse: "red"
        specular: "red"
        shininess: 50
    }

    /////////////////////assem3////////////////////////

    Mesh{
        id: sceneLoader3
        source: "qrc:/obj/assem3.obj"
    }

    Transform{
        id: sceneLoaderTransform3
        property real userDistanY: 0.0
        property real userDistanX: 0.0
        //translation: Qt.vector3d(-4.5, 3.3 , -1)      // X: -6 -> 0
        //scale: 0.01
        matrix: {
            var m1 = Qt.matrix4x4();
            m1.translate(Qt.vector3d(userDistanY, 3.3 , userDistanX));
            m1.scale(0.01, 0.01, 0.01)
            return m1;
        }
    }

    PhongMaterial {
        id: material3
        ambient: "gray"
        diffuse: "red"
        specular: "red"
        shininess: 50
    }

    /////////////////////////////////////////////////////////////////


    ////////////////////assem4///////////////////////
    Mesh{
        id: sceneLoader4
        source: "qrc:/obj/assem4.obj"
    }

    Transform{
        id: sceneLoaderTransform4
        property real userDistanZ: 6.5
        property real userDistanX: 0.5
        property real userDistanY: 0.65
        translation: Qt.vector3d(0.65, 7 , 0.7)      // Y: -2 -> 0.5   -2, -2 , 5.5
        scale: 0.01
        matrix: {
            var m = Qt.matrix4x4();
            m.translate(Qt.vector3d(userDistanY, userDistanZ , userDistanX));
            m.scale(0.01, 0.01, 0.01)
            return m;
        }
    }

    PhongMaterial {
        id: material4
        //  ambient: "gray"
//        diffuse: "red"
//        specular: "red"
//        shininess: 50
    }
    signal check(bool t)
    function myQmlFunction(msg: string){
        console.log("Got message:", msg)
        distanX = parseFloat(msg.split(","))
        distanY = parseFloat(msg.split(",")[1])
        distanZ = parseFloat(msg.split(",")[2])
        console.log("Got message:", distanY)
        console.log("Got message:", distanX)
        console.log("Got message:", distanZ)
        check(true)
    }
    QQ2.ParallelAnimation {
        id: trans

        QQ2.NumberAnimation {
            function myQmlFunction(msg: string){
                console.log("Got message:", msg)
                distanX = parseFloat(msg.split(","))
                distanY = parseFloat(msg.split(",")[1])
                distanZ = parseFloat(msg.split(",")[2])
                console.log("Got message:", distanY)
                console.log("Got message:", distanX)
                console.log("Got message:", distanZ)
                check(true)
            }
            target: sceneLoaderTransform2
            property: "userDistanX"
            //from: -6.0
            to: distanX
            duration: 10000
            //loops: QQ2.Animation.Infinite
        }
        QQ2.NumberAnimation {
            target: sceneLoaderTransform3
            property: "userDistanY"
            //from: -6.0
            to: distanY
            duration: 10000
            //loops: QQ2.Animation.Infinite
        }
        QQ2.NumberAnimation {
            target: sceneLoaderTransform3
            property: "userDistanX"
            //from: -6.0
            to: distanX
            duration: 10000
            //loops: QQ2.Animation.Infinite
        }
        QQ2.NumberAnimation {
            target: sceneLoaderTransform4
            property: "userDistanX"
           // from: -6.0
            to: distanX + userDistanX1
            duration: 10000
            //loops: QQ2.Animation.Infinite
        }
        QQ2.NumberAnimation {
            target: sceneLoaderTransform4
            property: "userDistanY"
            //from: -6.0
            to: distanY + userDistanY1
            duration: 10000
            //loops: QQ2.Animation.Infinite
        }
        QQ2.NumberAnimation {
            target: sceneLoaderTransform4
            property: "userDistanZ"
           // from: 10.0
            to: distanZ
            duration: 10000
            //loops: QQ2.Animation.Infinite
        }
        running: t
        }
    Entity{
        id: assem1Entity
        components: [sceneLoader, sceneLoaderTransform, material1]
    }
    Entity{
        id: assem2Entity
        components: [sceneLoader2, sceneLoaderTransform2, material3]
    }
    Entity{
        id: assem3Entity
        components: [sceneLoader3, sceneLoaderTransform3, material3]
    }
    Entity{
        id: assem4Entity
        components: [sceneLoader4, sceneLoaderTransform4, material4]
    }

}
