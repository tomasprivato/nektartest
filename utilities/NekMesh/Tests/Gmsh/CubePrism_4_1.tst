<?xml version="1.0" encoding="utf-8" ?>
<test>
    <description>Gmsh (v4.0) high-order prism cube, order 2</description>
    <executable>NekMesh</executable>
    <parameters>-m jac:list CubePrism_4_1.msh CubePrism_4_1.xml:xml:test</parameters>
    <files>
        <file description="Input File">CubePrism_4_1.msh</file>
    </files>
    <metrics>
        <metric type="regex" id="1">
            <regex>^Total negative Jacobians: (\d+)</regex>
            <matches>
                <match>
                    <field id="0">0</field>
                </match>
            </matches>
        </metric>
    </metrics>
</test>
